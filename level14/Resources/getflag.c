#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

char * ft_des(char *buff)
{
    char *str = strdup(buff);
    int key_idx = 0;
    char *key = "0123456";

    for (int i = 0; i < strlen(str); i++)
    {
        if (key_idx == 6)
            key_idx = 0;
        int shift = key[key_idx];
        if (i % 2 == 0)
        {
            for (int j = 0; j < shift; j++)
            {
                str[i]--;
                if (str[i] == 31)
                    str[i] = '~';
            }
        }
        else
        {
            for (int j = 0; j < shift; j++)
            {
                str[i]++;
                if (str[i] == 127)
                    str[i] = ' ';
            }
        }
        key_idx++;
    }
    return str;
}

int main(void)
{
    char buff[256];
    int fd;
    uid_t uid;

    if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0)
    {
        puts("You should not reverse this");
        return 1;
    }
    if (getenv("LD_PRELOAD") != NULL || open("/etc/ld.so.preload", O_RDONLY) > 0)
    {
        fprintf(stderr, "Injection Linked lib detected exit..\n");
        return 1;
    }
    fd = syscall_open("/proc/self/maps", O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "/proc/self/maps is unaccessible, probably a LD_PRELOAD attempt exit...\n");
        return 1;
    }
    while (syscall_gets(buffer, 256, fd) != 0)
    {
        if (afterSubstr(buffer, "00000000 00:00 0") == 0) {
            fprintf(stderr, "LD_PRELOAD detected through memory maps exit ..\n");
            return 0;
        }
    }
    printf("Check flag.Here is your token : ");
    uid = getuid();
    switch (uid) {
        case 0:
            printf("You are root are you that dumb ?\n");
            break;
        case 3000:
            puts(ft_des("I`fA>_88eEd:=`85h0D8HE>,D"));
            break;
        case 3001:
            puts(ft_des("7`4Ci4=^d=J,?>i;6,7d416,7"));
            break;
        case 3002:
            puts(ft_des("<>B16\\AD<C6,G_<1>^7ci>l4B"));
            break;
        case 3003:
            puts(ft_des(""));
            break;
        case 3004:
            puts(ft_des(""));
            break;
        case 3005:
            puts(ft_des(""));
            break;
        case 3006:
            puts(ft_des(""));
            break;
        case 3007:
            puts(ft_des(""));
            break;
        case 3008:
            puts(ft_des(""));
            break;
        case 3009:
            puts(ft_des(""));
            break;
        case 3010:
            puts(ft_des(""));
            break;
        case 3011:
            puts(ft_des(""));
            break;
        case 3012:
            puts(ft_des(""));
            break;
        case 3013:
            puts(ft_des(""));
            break;
        case 3014:
            puts(ft_des(""));
            break;
        default:
            printf("\nNope there is no token here for you sorry. Try again :)\n");
            break;
    }
    return 0;
}
