#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>


#define SERV_SOCKET_NAME "server.soc"
#define RECV_BUF_LEN 64

static int sock;

void clean(int sock_fd) {
    close(sock_fd);
    unlink(SERV_SOCKET_NAME);
}


void sighandler(int signum) {
    printf("\n[::] Shut downing server...");
    clean(sock);
    exit(0);
}

int main() {
    struct sockaddr_un server_address = {};
    socklen_t client_length = sizeof (struct sockaddr_un);

    struct sockaddr_un client_address = {};
    socklen_t address_length = sizeof(struct sockaddr_un);

    ssize_t bytes_recv;

    char buffer[RECV_BUF_LEN];
    char resp[2*RECV_BUF_LEN];

    //    * Домен сокета обозначает тип соединения. AF_UNIX - сокет в файловом пространстве имен.
    //    * Тип сокета. Значение SOCK_DGRAM указывает датаграммный сокет (в пр-ве файловых имен
    //    датаграммные сокеты также надежны, как и потоковые сокеты).
    //    * Протокол, используемый для передачи данных. (TCP/UDP) 0 - протокол выбирается по умолчанию.
    //    В случае ошибки функция socket() возвращает -1.
    sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Cannot create socket");
        return 1;
    }

    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, SERV_SOCKET_NAME, sizeof(SERV_SOCKET_NAME));

    // bind() - связывает сокет с заданным адресом.
    // После вызова bind() программа-сервер становится доступна для соединения по заданному адресу (имени файла)
    if (bind(
            sock,
            (struct sockaddr *)&server_address,
            address_length) == -1) {
        perror("Cannot bind socket");
        return 1;
    }

    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);
    printf("[::] Echo Server is working.\n(Press Ctrl + C to stop)\n");

    socklen_t cli_len = client_length;
    for (;;) {
        bytes_recv = recvfrom(
                sock,
                buffer,
                sizeof(buffer),
                0,
                (struct sockaddr *)&client_address,
                &cli_len
        );

        if (bytes_recv < 0) {
            perror("recvfrom() call failed");
            clean(sock);
            return 1;
        }

        buffer[bytes_recv] = '\0';

        snprintf(resp, 2*RECV_BUF_LEN, "%s (SRV PID: %d)", buffer, getpid());

        printf("[*] Client %s sent: %s\n", client_address.sun_path, resp);

        if (sendto(sock, resp, strlen(resp), 0, (struct sockaddr *)&client_address, client_length) < 0) {
            perror("Cannot send datagram message");
        }

        cli_len = client_length;
    }
}
