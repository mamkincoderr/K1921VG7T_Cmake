<#
 Скачивает инструменты проекта в tools\ (в git они не хранятся):
   tools\gcc      GCC НИИЭТ 12.2.1 (riscv64-unknown-elf), GitFlic niiet/vscode_toolkit, ветка riscv_gcc_windows
   tools\openocd  OpenOCD НИИЭТ с драйвером Flash К1921ВГ7Т, GitFlic niiet/openocd, релиз v1.0.0
 Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 Telegram: https://t.me/oDeXteRo

 gitflic.ru часто не резолвится DNS провайдера. Скрипт спрашивает адрес у 8.8.8.8 и
 подставляет его только для git и curl, системные настройки не меняются.
#>
$ErrorActionPreference = 'Stop'
$Root = Split-Path -Parent $PSScriptRoot
$Tools = Join-Path $Root 'tools'

function Resolve-GitFlic {
    try { [void][System.Net.Dns]::GetHostAddresses('gitflic.ru'); return 'gitflic.ru' } catch { }
    # через cmd: nslookup пишет в stderr, а при $ErrorActionPreference = 'Stop' Windows PowerShell 5.1
    # считает любой вывод native-программы в stderr ошибкой
    $line = cmd /c 'nslookup gitflic.ru 8.8.8.8 2>nul' | Select-String 'Address' | Select-Object -Last 1
    if (-not $line) { throw 'Не удалось определить адрес gitflic.ru' }
    return ($line.ToString() -replace '.*?(\d+\.\d+\.\d+\.\d+).*', '$1')
}

$ip = Resolve-GitFlic
$resolve = if ($ip -eq 'gitflic.ru') { @() } else { @('--resolve', "gitflic.ru:443:$ip") }
$gitOpt  = if ($ip -eq 'gitflic.ru') { @() } else { @('-c', "http.curloptResolve=gitflic.ru:443:$ip") }

# ---- GCC ----------------------------------------------------------------
$gcc = Join-Path $Tools 'gcc'
if (-not (Test-Path (Join-Path $gcc 'bin\riscv64-unknown-elf-gcc.exe'))) {
    Write-Host 'Скачивание GCC НИИЭТ (около 600 МБ) ...'
    $tmp = Join-Path $Tools 'gcc_clone'
    if (Test-Path $tmp) { Remove-Item -Recurse -Force $tmp }
    git @gitOpt clone --depth 1 -b riscv_gcc_windows https://gitflic.ru/project/niiet/vscode_toolkit.git $tmp
    if ($LASTEXITCODE -ne 0) { throw 'git clone не удался' }
    Remove-Item -Recurse -Force (Join-Path $tmp '.git')
    if (Test-Path $gcc) { Remove-Item -Recurse -Force $gcc }
    Rename-Item $tmp 'gcc'
}
& (Join-Path $gcc 'bin\riscv64-unknown-elf-gcc.exe') --version | Select-Object -First 1

# ---- Псевдонимы компилятора для индексатора MRS ----------------------------------
# Встроенное обнаружение настроек компилятора в MRS запускает riscv-none-elf-gcc, а у пакета
# НИИЭТ префикс riscv64-unknown-elf-. Жёсткие ссылки в том же каталоге не занимают места,
# а GCC по-прежнему находит свои файлы рядом с собой.
foreach ($n in 'gcc', 'g++') {
    $alias  = Join-Path $gcc "bin/riscv-none-elf-$n.exe"
    $target = Join-Path $gcc "bin/riscv64-unknown-elf-$n.exe"
    if (-not (Test-Path -LiteralPath $alias)) {
        cmd /c "mklink /H `"$alias`" `"$target`"" | Out-Null
    }
}

# ---- OpenOCD ------------------------------------------------------------
$ocd = Join-Path $Tools 'openocd'
if (-not (Test-Path (Join-Path $ocd 'bin/openocd.exe'))) {
    $zip = Join-Path $Tools 'sc-dt_Patch_Niiet_Win32.zip'
    if (-not (Test-Path $zip)) {
        Write-Host 'Скачивание OpenOCD НИИЭТ ...'
        # Ссылка из README SDK НИИЭТ устарела (даёт 404), поэтому ищем файл на странице релиза.
        $page = 'https://gitflic.ru/project/niiet/openocd/release'
        $ok = $false
        try {
            $html = (curl.exe -sSL --fail @resolve $page) -join "`n"
            $rel  = [regex]::Match($html, '/project/niiet/openocd/release/[0-9a-f-]{36}').Value
            if ($rel) {
                $html2 = (curl.exe -sSL --fail @resolve "https://gitflic.ru$rel") -join "`n"
                # на странице релиза у каждого файла своя ссылка download; пробуем их по очереди
                # и берём первую, внутри которой лежит каталог tools/bin/openocd.exe
                foreach ($m in [regex]::Matches($html2, "$rel/[0-9a-f-]{36}/download")) {
                    $tmp = Join-Path $Tools 'openocd_candidate.zip'
                    curl.exe -sSL --fail @resolve -o $tmp "https://gitflic.ru$($m.Value)" 2>$null
                    if ($LASTEXITCODE -eq 0 -and (Test-Path $tmp) -and (Get-Item $tmp).Length -gt 1MB) {
                        try {
                            Add-Type -AssemblyName System.IO.Compression.FileSystem
                            $z = [System.IO.Compression.ZipFile]::OpenRead($tmp)
                            $has = $z.Entries | Where-Object { $_.FullName -like 'tools/bin/openocd.exe' }
                            $z.Dispose()
                            if ($has) { Move-Item $tmp $zip -Force; $ok = $true; break }
                        } catch { }
                    }
                    Remove-Item $tmp -ErrorAction SilentlyContinue
                }
            }
        } catch { }
        if (-not $ok) {
            Write-Host 'Не удалось скачать OpenOCD автоматически.' -ForegroundColor Yellow
            Write-Host "Скачайте sc-dt_Patch_Niiet_Win32.zip со страницы $page и положите в $Tools, затем запустите fetch.ps1 снова."
            throw 'OpenOCD не скачан'
        }
    }
    $x = Join-Path $Tools 'openocd_unpack'
    Expand-Archive $zip -DestinationPath $x -Force
    New-Item -ItemType Directory -Force $ocd | Out-Null
    Copy-Item (Join-Path $x 'tools/bin')   $ocd -Recurse -Force
    Copy-Item (Join-Path $x 'tools/share') $ocd -Recurse -Force
    Remove-Item -Recurse -Force $x, $zip
}
& (Join-Path $ocd 'bin/openocd.exe') --version 2>&1 | Select-Object -First 1
Write-Host 'Инструменты готовы'
