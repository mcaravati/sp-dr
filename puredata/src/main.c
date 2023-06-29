#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "tinyosc/tinyosc.h"

#define PORT 9000
#define BUFFER_SIZE 2048

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    struct sockaddr_in destination;

    // Create a UDP socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        fprintf(stderr, "Error creating socket\n");
        perror("socket");
        return 1;
    }

    memset(&destination, 0, sizeof(destination));

    // Configure destination
    destination.sin_family = AF_INET;
    destination.sin_port = htons(PORT);
    destination.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    char buffer[BUFFER_SIZE] = {0};
    int len = tosc_writeMessage(buffer, sizeof(buffer), "/set-motor", "ii", 2, 130);

    if (connect(fd, (struct sockaddr *)&destination, sizeof(destination)) < 0)
    {
        fprintf(stderr, "Error connecting socket\n");
        perror("connect");
        return 1;
    }

    int result = send(fd, buffer, len, 0);
    if (result < 0)
    {
        fprintf(stderr, "Error sending message\n");
        perror("send");
        return 1;
    }
}