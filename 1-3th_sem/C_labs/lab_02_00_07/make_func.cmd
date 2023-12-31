@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Wpedantic -Wextra -Werror -Wvla -O0 -pg main.c -o app.exe
.\data_generator.py
.\app.exe < my_data.txt > out.txt
gprof app.exe > out_prof_inf.txt