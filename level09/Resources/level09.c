#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>

int syscall_open(const char *path, int flags)
{
    return syscall(SYS_open, path, flags);
}

int main(int argc, char **argv)
{
    int fd;
    char *input;
    size_t len;

    if (ptrace(PTRACE_TRACEME, 0, 1, 0) < 0)
    {
        puts("You should not reverse this");
        return 1;
    }
    if (getenv("LD_PRELOAD") != NULL)
    {
        fwrite("Injection Linked lib detected exit..\n", 1, 0x25, stderr);
        return 1;
    }
    if (open("/etc/ld.so.preload", 0) >= 0)
    {
        fwrite("Injection Linked lib detected exit..\n", 1, 0x25, stderr);
        return 1;
    }
    fd = syscall_open("/proc/self/maps", 0);
    if (fd == -1)
    {
        fwrite("/proc/self/maps is unaccessible...\n", 1, 0x46, stderr);
        return 1;
    }
    if (argc != 2)
    {
        fwrite("You need to provied only one arg.\n", 1, 0x22, stderr);
        return 1;
    }
    input = argv[1];
    len = strlen(input);
    for (size_t i = 0; i < len; i++)
        putchar(input[i] + i);
    putchar('\n');
    return 0;
}
