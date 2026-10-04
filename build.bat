@echo off
rem Построитель для MounRiver Studio: MRS вызывает этот файл как "make" для Build, Clean и Build Targets.
rem Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
rem Telegram: https://t.me/oDeXteRo
rem
rem Цель берётся из аргументов (Eclipse добавляет свои ключи вроде -j24, они пропускаются):
rem   all         сборка приложения
rem   clean       очистка каталога сборки
rem   flash       прошивка по JTAG
rem   uart        прошивка через UART-загрузчик
rem   boot-flash  установка UART-загрузчика по JTAG (один раз)
setlocal EnableExtensions

set "TARGET=all"
for %%A in (%*) do call :scan "%%~A"
goto :scanned

:scan
rem Аргумент может прийти одной строкой вида "-j24 all": разбираем по словам
for %%B in (%~1) do call :word "%%~B"
exit /b 0

:word
set "W=%~1"
if not "%W:~0,1%"=="-" set "TARGET=%W%"
exit /b 0

:scanned
set "CMD=%TARGET%"
if /i "%CMD%"=="all" set "CMD=build"

rem CMake и Ninja: MRS их не содержит, а PATH, унаследованный средой, мог устареть. Ищем в
rem стандартных местах, чтобы не перезапускать MRS после установки.
for %%D in ("%ProgramFiles%\CMake\bin" "%ProgramW6432%\CMake\bin" "%LOCALAPPDATA%\Programs\CMake\bin" "%LOCALAPPDATA%\Microsoft\WinGet\Links" "%ProgramFiles%\Ninja") do (
    if exist "%%~D\" set "PATH=%PATH%;%%~D"
)
for /d %%P in ("%LOCALAPPDATA%\Microsoft\WinGet\Packages\Ninja-build.Ninja*") do set "PATH=%PATH%;%%~P"

echo [K1921] target=%CMD%
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\run.ps1" %CMD%
exit /b %ERRORLEVEL%
