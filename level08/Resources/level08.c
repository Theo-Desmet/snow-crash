#include <stdio.h>
#include <strings.h>
#include <fcntl.h>
#include <err.h>

int main(int ac, char **av, char **envp)
{
    int fd;
    char buff[1024];
    size_t content_size;

    if (ac == 1)
    {
        printf("%s [file to read]\n", *av);
        exit(1);
    }
    if (strstr(av[1], "token") == NULL)
    {
        printf("You may not access \'%s\'\n", av[1]);
        exit(1);
    }
    fd = open(av[1], 0);
    if (fd == -1)
        err(1, "Unable to open %s", av[1]);
    content_size = read(fd, buff, 0x400);
    if (content_size == 0xffffffff)
        err(1, "Unable to read fd %d", fd);
    return write(1, buff, fd);
}
