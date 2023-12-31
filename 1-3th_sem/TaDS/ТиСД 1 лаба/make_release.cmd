@ECHO OFF

CHCP 65001

gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -c main.c

gcc -o main.exe main.o