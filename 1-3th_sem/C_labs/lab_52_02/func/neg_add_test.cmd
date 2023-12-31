@ECHO OFF
IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe conv neg_add_%~1_in.txt
..\app.exe ab neg_add_%~1_in.bin < neg_add_%~1_new_prod.txt
IF %ERRORLEVEL% EQU 0 ECHO NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
..\app.exe pb neg_add_%~1_in.bin > out.txt
DEL neg_add_%~1_in.bin
FC /N neg_add_%~1_out.txt out.txt
DEL out.txt
:END