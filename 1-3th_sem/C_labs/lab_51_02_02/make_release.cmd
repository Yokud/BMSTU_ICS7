@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror  -Wvla -c main.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror  -Wvla -c files.c
gcc -o app.exe main.o files.o