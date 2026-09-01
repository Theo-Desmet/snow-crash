#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    char *file;
    char *host;
    int sockfd;
    int fd;
    ssize_t bytes_read;
    struct sockaddr_in sin;
    char buffer[4096];

    if (argc < 3) {
        printf("%s file host\n\tsends file to host if you have access to it\n", argv[0]);
        exit(1);
    }

    file = argv[1];
    host = argv[2];
    if (access(file, 4) != 0)
    {
        printf("You don't have access to %s\n", file);
        return 0;
    }
    printf("Connecting to %s:6969 .. ", host);
    fflush(stdout);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(host);
    sin.sin_port = htons(6969);
    if (connect(sockfd, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
        printf("Unable to connect to host %s\n", host);
        exit(1);
    }
    if (write(sockfd, ".*( )*.\n", 8) == -1) {
        printf("Unable to write banner to host %s\n", host);
        exit(1);
    }
    printf("Connected!\nSending file .. ");
    fflush(stdout);
    fd = open(file, O_RDONLY);
    if (fd == -1) {
        puts("Damn. Unable to open file");
        exit(1);
    }
    bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        printf("Unable to read from file: %s\n", strerror(errno));
        exit(1);
    }
    write(sockfd, buffer, bytes_read);
    puts("wrote file!");
    return 0;
}
