@ECHO OFF
IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe conv pos_add_%~1_in.txt
..\app.exe ab pos_add_%~1_in.bin < pos_add_%~1_new_prod.txt
IF %ERRORLEVEL% NEQ 0 ECHO POS TEST %~1 ::FAIL:: RETURN CODE IS NOT ZERO... & GOTO :END
..\app.exe pb pos_add_%~1_in.bin >> out.txt
DEL pos_add_%~1_in.bin
FC /N pos_add_%~1_out.txt out.txt
DEL out.txt
:END