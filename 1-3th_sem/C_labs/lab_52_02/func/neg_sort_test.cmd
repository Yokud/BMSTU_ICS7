@ECHO OFF
IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe conv neg_sort_%~1_in.txt
..\app.exe sb neg_sort_%~1_in.bin neg_sort_%~1_out.bin
IF %ERRORLEVEL% EQU 0 ECHO NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
DEL neg_sort_%~1_in.bin
..\app.exe pb neg_sort_%~1_out.bin >> out.txt
DEL neg_sort_%~1_out.bin
FC /N neg_sort_%~1_out.txt out.txt
DEL out.txt
:END