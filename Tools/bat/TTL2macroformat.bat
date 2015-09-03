@echo off
REM TTLファイルをNetworkCommanderのマクロ内で使用するフォーマットに変換する
REM フォーマット ttlを'<''>'で囲う
REM 例：<sendln 'message'>
set INFILE=%~dpnx1
set OUTFILE=%~dpnx2

if not defined INFILE (
    goto USAGE
)
if not defined OUTFILE (
    goto USAGE
)

for /F "delims=" %%A in (%INFILE%) do (
    echo ^<%%A^>>>%OUTFILE%
)
goto END

:USAGE
echo USAGE: %~nx0 ^<input file^> ^<output file^>
echo.

:END
