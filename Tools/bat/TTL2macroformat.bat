@echo off
REM TTL�t�@�C����NetworkCommander�̃}�N�����Ŏg�p����t�H�[�}�b�g�ɕϊ�����
REM �t�H�[�}�b�g ttl��'<''>'�ň͂�
REM ��F<sendln 'message'>
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
