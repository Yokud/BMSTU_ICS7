@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -O0 --coverage main.c files.c txt_to_bin.c products.c -o app.exe
PUSHD func
CALL ./all_test.cmd
PUSHD ..
gcov main.c files.c products.c