#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>


#define SERVER_SOCK_NAME "server.soc"

#define BUF_SIZE 64

int socket_fd;

void clean(int sock_fd, char* sock_name)
{
    close(sock_fd);
    unlink(sock_name);
}


int main(int argc, char *argv[]) {
    char *sock_name = argv[1];
    char *message = argv[2];

    struct sockaddr_un client_address, server_address;
    socklen_t address_length = sizeof(struct sockaddr_un);
    char buffer[BUF_SIZE];
    ssize_t bytes_recv;


    socket_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (socket_fd == -1) {
        perror("socket call error");
        return 1;
    }

    client_address.sun_family = AF_UNIX;
    strncpy(client_address.sun_path, sock_name, strlen(sock_name));

    if (bind(socket_fd,
             (const struct sockaddr *)&client_address,
             address_length) == -1) {
        perror("client: bind");
        return 1;
    }


    server_address.sun_family = AF_UNIX;
    strncpy(server_address.sun_path, SERVER_SOCK_NAME, strlen(SERVER_SOCK_NAME));

    snprintf(buffer, BUF_SIZE, "%s (PID: %d)", message, getpid());
    if (sendto(socket_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_address, address_length) == -1) {
        perror("sendto call error");
        return 1;
    }

    printf("[->] %s\n", buffer);
    bytes_recv = recvfrom(
            socket_fd,
            buffer,
            sizeof (buffer),
            0,
            (struct sockaddr*)&server_address,
            &address_length
    );

    if (bytes_recv < 0 ) {
        perror("recvfrom() call failed");
        clean(socket_fd, sock_name);
        return 1;
    }

    buffer[bytes_recv] = '\0';

    printf("[<-] %s\n", buffer);

    clean(socket_fd, sock_name);

    return 0;
}
