%.o : %.c
	gcc -c $< -std=c99 -Wall -Wpedantic -Wextra -Werror
app.exe: main.o structures.o utils.o
	gcc -o app.exe main.o structures.o utils.o
clean:
	rm *.o *.exe
