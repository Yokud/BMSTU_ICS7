CC = gcc
INCLUDE_DIR = include
OBJ = $(wildcard *.c)
FLAGS = -Werror -Wall -std=c99

app1.exe:
	${CC} ${OBJ} -I${INCLUDE_DIR} ${FLAGS} -o app1.exe

clean:
	rm *.o *.exe *.out

run: app1.exe
	./app1.exe