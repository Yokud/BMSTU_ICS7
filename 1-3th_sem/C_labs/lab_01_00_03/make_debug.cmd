@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -g3 -c main.c
gcc -o app.exe main.o