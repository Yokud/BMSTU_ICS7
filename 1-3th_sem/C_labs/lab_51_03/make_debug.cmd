@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -g3 -c main.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -g3 -c files.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -g3 -c txt_to_bin.c
gcc -o app.exe main.o files.o txt_to_bin.o