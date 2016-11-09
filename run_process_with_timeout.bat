SET EXE=%2
start %1%EXE%
timeout /t %3

FOR /F %%x IN ('tasklist /NH /FI "IMAGENAME eq %EXE%"') DO IF %%x == %EXE% taskkill /im %EXE% /f & exit /b 1
exit /b %errorlevel%