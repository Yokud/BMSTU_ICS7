CC = gcc
INCLUDE_DIR = include
OBJ = $(wildcard *.c)
FLAGS = -Werror -Wall -std=c99

app2.exe:
	${CC} ${OBJ} -I${INCLUDE_DIR} ${FLAGS}  -o app2.exe

clean:
	rm *.o *.exe *.out

run: app2.exe
	./app2.exe