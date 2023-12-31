CC=gcc
WORKDIR=src

app.exe:
	$(CC) $(WORKDIR)/main.c -o app.exe

run: app.exe
	sudo ./app.exe

log:
	sudo cat /var/log/syslog

clean:
	rm *.out *.exe *.o
