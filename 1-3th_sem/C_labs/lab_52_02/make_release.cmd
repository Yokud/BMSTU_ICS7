@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -c main.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -c files.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -c txt_to_bin.c
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -c products.c
gcc -o app.exe main.o files.o txt_to_bin.o products.o