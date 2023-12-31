@ECHO OFF
IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe conv neg_print_by_substr_%~1_in.txt
..\app.exe fb neg_print_by_substr_%~1_in.bin banana > out.txt
IF %ERRORLEVEL% EQU 0 ECHO NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
DEL neg_print_by_substr_%~1_in.bin
FC /N neg_print_by_substr_%~1_out.txt out.txt
DEL out.txt
:END