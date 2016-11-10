SET EXE=%2
SET FINISHED=0
start %1%EXE% && %FINISHED%=1

FOR /L %%I in (1,1,%3) DO (timeout /t 1 && IF %%I EQU %3 goto :timeout && IF FINISHED EQU 1 goto :taskFinished)
:taskFinished
exit /b %errorlevel%
:timeout
FOR /F %%x IN ('tasklist /NH /FI "IMAGENAME eq %EXE%"') DO IF %%x == %EXE% taskkill /im %EXE% /f & exit /b 1