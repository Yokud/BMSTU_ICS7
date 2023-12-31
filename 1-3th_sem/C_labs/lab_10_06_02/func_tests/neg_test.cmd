@ECHO OFF

IF "%1"=="" ECHO NOT ENOUGH PARAMETERS... & GOTO :END

set /p args=<neg_%~1_args.txt

drmemory -lib_blacklist "*" -batch -prefix_style 2 -logdir ..\out\ -- ..\app.exe %args% <neg_%~1_in.txt >out.txt

IF %ERRORLEVEL% EQU 0 ECHO NEG TEST %~1 ::FAIL:: RETURN CODE IS ZERO... & GOTO :END

FC /N neg_%~1_out.txt out.txt

DEL out.txt

:END
