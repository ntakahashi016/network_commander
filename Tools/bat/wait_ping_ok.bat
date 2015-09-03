@echo off
if "%1" EQU "" (
    echo no ipaddress
    pause
    goto end
)
set COUNT=0
:loop
:notrespond
ping -n 1 %1 | find "ms TTL=" > NUL
if ERRORLEVEL 1 (
    set COUNT=0
    echo ping %1 NG
    goto notrespond
)
set /a COUNT=COUNT+1
echo ping %1 OK:%COUNT%
if "%COUNT%" == "3" goto end
goto loop
:end
