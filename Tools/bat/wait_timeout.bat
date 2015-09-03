@echo off
if "%1" EQU "" (
    echo no time
    pause
    goto end
)
echo. %2
timeout %1