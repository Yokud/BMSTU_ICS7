@ECHO OFF
IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe conv pos_%~1_in.txt
..\app.exe s pos_%~1_in.bin
..\app.exe p pos_%~1_in.bin > out.txt
DEL pos_%~1_in.bin
IF %ERRORLEVEL% NEQ 0 ECHO POS TEST %~1 ::FAIL:: RETURN CODE IS NOT ZERO... & GOTO :END
FC /N pos_%~1_out.txt out.txt
:END