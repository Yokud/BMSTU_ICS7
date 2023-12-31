@ECHO OFF
IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe conv pos_print_by_substr_%~1_in.txt
..\app.exe fb pos_print_by_substr_%~1_in.bin banana > out.txt
DEL pos_print_by_substr_%~1_in.bin
IF %ERRORLEVEL% NEQ 0 ECHO POS TEST %~1 ::FAIL:: RETURN CODE IS NOT ZERO... & GOTO :END
FC /N pos_print_by_substr_%~1_out.txt out.txt
DEL out.txt
:END