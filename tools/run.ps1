<#
 Драйвер проекта K1921VG7T. Все кнопки MRS и все сценарии из терминала идут через него.
 Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 Telegram: https://t.me/oDeXteRo

 Запуск: powershell -ExecutionPolicy Bypass -File tools\run.ps1 <команда> [-Port COMx]

 Команды
   build        настроить (если нужно) и собрать приложение и загрузчик
   clean        удалить каталог сборки
   flash        записать K1921VG7T_Cmake.elf по JTAG (OpenOCD НИИЭТ), проверить, перезапустить
   boot-flash   записать UART-загрузчик по JTAG в 0x0000 (нужно один раз; он собирается вместе с приложением)
   uart         записать K1921VG7T_Cmake.bin через UART-загрузчик
   erase        стереть всю Flash 512 КБ по JTAG (загрузчик тоже стирается)
   debug        запустить OpenOCD в отдельном окне и открыть GDB с K1921VG7T_Cmake.elf
   info         прочитать IDCODE и misa по JTAG
   size         показать размеры секций образа

 Размещение во Flash одно: загрузчик 0x0000-0x1FFF, приложение с 0x2000.
#>
param(
    [Parameter(Position = 0)][string]$Command = 'help',
    [string]$Port = ''
)
$ErrorActionPreference = 'Stop'

# Вывод в консоль MRS (и любой перенаправленный вывод) должен идти в системной кодировке Windows
# (для русской локали 1251), потому что Eclipse читает именно её. Без этого кириллица
# выходит в OEM-кодировке 866 и в консоли MRS превращается в нечитаемые символы.
if ([Console]::IsOutputRedirected) {
    try { [Console]::OutputEncoding = [System.Text.Encoding]::Default } catch { }
}

$Root     = Split-Path -Parent $PSScriptRoot
$BuildDir = Join-Path $Root 'obj'
$GccBin   = Join-Path $Root 'tools\gcc\bin'
$OcdDir   = Join-Path $Root 'tools\openocd'
$OcdExe   = Join-Path $OcdDir 'bin\openocd.exe'
$Prefix   = 'riscv64-unknown-elf-'
$AppElf   = Join-Path $BuildDir 'K1921VG7T_Cmake.elf'
$AppBin   = Join-Path $BuildDir 'K1921VG7T_Cmake.bin'
$BootElf  = Join-Path $BuildDir 'bootloader\bootloader.elf'

function ToTcl([string]$p) { return '{' + $p.Replace([string][char]92, '/') + '}' }

function Need([string]$path, [string]$hint) {
    if (-not (Test-Path $path)) { throw "$path не найден. $hint" }
}

function Add-ToolPath {
    Need (Join-Path $GccBin "${Prefix}gcc.exe") 'Сначала запустите tools\fetch.ps1.'
    $env:PATH = "$GccBin;$env:PATH"
}

function Invoke-Ocd([string[]]$Cmds, [switch]$Background) {
    Need $OcdExe 'Сначала запустите tools\fetch.ps1.'
    $args_ = @('-s', 'share/openocd/scripts',
               '-f', (Join-Path $Root 'openocd\dap_vg7t.cfg').Replace([string][char]92, '/'),
               '-f', 'target/k1921vg7t.cfg',
               '-f', (Join-Path $Root 'openocd\k1921_tools.cfg').Replace([string][char]92, '/'),
               '-c', 'reset_config none')
    foreach ($c in $Cmds) { $args_ += @('-c', $c) }
    Push-Location $OcdDir
    try {
        if ($Background) {
            return Start-Process -FilePath $OcdExe -ArgumentList $args_ -PassThru
        }
        & $OcdExe @args_
        if ($LASTEXITCODE -ne 0) { throw "OpenOCD завершился с ошибкой (код $LASTEXITCODE)" }
    } finally { Pop-Location }
}

# Python с модулем pyserial. Каталог GCC НИИЭТ (tools\gcc\bin) содержит собственный python.exe без
# pyserial, а Add-ToolPath ставит этот каталог в начало PATH, поэтому интерпретатор ищется явно:
# перебираются все python из PATH, кроме каталога GCC, и берётся первый, где импортируется serial.
$script:PyExe = $null
function Find-Python {
    if ($script:PyExe) { return $script:PyExe }
    $cands = @(Get-Command python, py -All -ErrorAction SilentlyContinue |
               Where-Object { $_.Source -notlike "$GccBin*" -and $_.Source -notlike '*\WindowsApps\*' } |
               ForEach-Object { $_.Source })
    foreach ($c in $cands) {
        & $c -c 'import serial' 2>$null
        if ($LASTEXITCODE -eq 0) { $script:PyExe = $c; return $c }
    }
    return $null
}

# Аппаратный сброс МК импульсом DTR через USB-UART платы (перемычка XP4). Заменяет программный
# сброс RSTSYS: после нескольких таких сбросов подряд флеш-контроллер зависал (STAT.BUSY=1 после
# любой команды), а аппаратный сброс его оживляет.
function Reset-Board {
    $py = Find-Python
    if (-not $py) { Write-Host 'Не найден Python с модулем pyserial (pip install pyserial), аппаратный сброс пропущен'; return }
    & $py (Join-Path $Root 'tools\uart_flash.py') --reset
    if ($LASTEXITCODE -ne 0) { Write-Host 'Аппаратный сброс не удался (нет порта CH340 или он занят)' }
}

# Настройка CMake при первом запуске; без цели собирается всё: приложение и загрузчик
function Do-Build([string]$Target = '') {
    Add-ToolPath
    if (-not (Test-Path (Join-Path $BuildDir 'build.ninja'))) {
        cmake --preset default
        if ($LASTEXITCODE -ne 0) { throw 'Не удалась настройка CMake' }
    }
    if ($Target) { cmake --build --preset default --target $Target }
    else         { cmake --build --preset default }
    if ($LASTEXITCODE -ne 0) { throw 'Сборка не удалась' }
}

switch ($Command) {
    'build' { Do-Build }

    'clean' {
        if (Test-Path $BuildDir) { Remove-Item -Recurse -Force $BuildDir }
        Write-Host "Удалено: $BuildDir"
    }

    'flash' {
        Do-Build
        # Импульс DTR только до записи: оживляет зависший флеш-контроллер.
        # После записи камень пускает k1921_run, не линия загрузчика.
        Reset-Board
        Invoke-Ocd @('init', 'halt', 'k1921_prepare',
                     "program $(ToTcl $AppElf) verify",
                     'k1921_run',
                     'shutdown')
    }

    'boot-flash' {
        Do-Build 'bootloader'
        Need $BootElf 'Сборка загрузчика не удалась?'
        Reset-Board
        Invoke-Ocd @('init', 'halt', 'k1921_prepare',
                     "program $(ToTcl $BootElf) verify",
                     'k1921_run',
                     'shutdown')
    }

    'uart' {
        Do-Build
        $py = Find-Python
        if (-not $py) { throw 'Не найден Python с модулем pyserial: pip install pyserial' }
        $a = @((Join-Path $Root 'tools\uart_flash.py'), $AppBin)
        if ($Port) { $a += @('--port', $Port) }
        & $py @a
        if ($LASTEXITCODE -ne 0) { throw 'Прошивка по UART не удалась' }
    }

    'erase' {
        Reset-Board
        Invoke-Ocd @('init', 'halt', 'k1921_prepare', 'flash erase_address 0x0 0x80000', 'shutdown')
    }

    'debug' {
        Do-Build
        Add-ToolPath
        $ocd = Invoke-Ocd @('init') -Background
        Start-Sleep -Seconds 2
        try {
            & (Join-Path $GccBin "${Prefix}gdb.exe") $AppElf -x (Join-Path $Root 'openocd\gdbinit')
        } finally {
            if (-not $ocd.HasExited) { Stop-Process -Id $ocd.Id -Force }
        }
    }

    'info' {
        Invoke-Ocd @('init', 'halt', 'resume', 'shutdown')
    }

    'size' {
        Add-ToolPath
        & "${Prefix}size.exe" -A $AppElf
    }

    default { Get-Help $PSCommandPath | Out-String | Write-Host }
}
