@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -O0 --coverage main.c my_string.c -o app.exe
.\app.exe
gcov main.c my_string.c