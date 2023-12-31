@ECHO OFF
IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe conv pos_sort_%~1_in.txt
..\app.exe sb pos_sort_%~1_in.bin pos_sort_%~1_out.bin
DEL pos_sort_%~1_in.bin
IF %ERRORLEVEL% NEQ 0 ECHO POS TEST %~1 ::FAIL:: RETURN CODE IS NOT ZERO... & GOTO :END
..\app.exe pb pos_sort_%~1_out.bin >> out.txt
DEL pos_sort_%~1_out.bin
FC /N pos_sort_%~1_out.txt out.txt
DEL out.txt
:END