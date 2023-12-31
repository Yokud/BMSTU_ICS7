CC=gcc
WORKDIR=src
FLAGS=-Wall -Werror -pthread

app.exe:
	$(CC) $(FLAGS) $(WORKDIR)/main.c -o app.exe

run: app.exe
	sudo ./app.exe

log:
	sudo cat /var/log/syslog

clean:
	rm *.out *.exe *.o
