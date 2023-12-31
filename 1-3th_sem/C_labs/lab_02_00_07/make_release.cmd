@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -pg -Wvla -c main.c
gcc -pg -o app.exe main.o