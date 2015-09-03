@echo off
rem 権限確認
openfiles >nul
if %errorlevel%==1 (
    echo.
    echo ！！！管理者として実行してください。！！！
    pause >nul
    goto quit
)
set TYPE=%1
set HOSTIP=%2
set MASK=%3
set DEFAULTGW=%4
if not defined TYPE (
    goto quit
)
if "%TYPE%" EQU "static" (
    if not defined HOSTIP (
        goto quit
    ) else if not defined MASK (
        goto quit
    ) else if not defined DEFAULTGW (
        goto quit
    )
)
echo %TYPE% %HOSTIP% %MASK% %DEFAULTGW%
netsh interface ip set address "ローカル エリア接続" %TYPE% %HOSTIP% %MASK% %DEFAULTGW%
:quit
exit /b
