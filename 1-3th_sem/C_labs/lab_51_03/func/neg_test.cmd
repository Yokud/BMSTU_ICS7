@ECHO OFF
IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END
..\app.exe conv neg_%~1_in.txt
IF %ERRORLEVEL% EQU 0 ECHO NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
..\app.exe s neg_%~1_in.txt
IF %ERRORLEVEL% EQU 0 ECHO NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END
..\app.exe p neg_%~1_in.txt > out.txt
DEL neg_%~1_in.bin
FC /N neg_%~1_out.txt out.txt
:END