# Level 09

1) La commande `ls` nous donne ceci:

```bash

```

2) Apres avoir decompile le binaire `level09` nous obtenons ceci:

```C
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
```

Le programme fait juste un chiffrement cesar de ce qu'on a entre en argument pour chaque characteres par rapport a sa position dans la phrase.

3) Nous voyons aussi que le fichier `token` contient egalement notre token chiffre:

```bash
cat token
f4kmm6p|=�p�n��DB�Du{��
```

4) L'idee est de faire un programme python qui va faire l'inverse que ce que fait notre programme pour dechiffrer `token`

```python
import sys

def decrypt(str) -> str:
    new_str = ""
    for (index, c) in enumerate(str):
        ascii_val: int = ord(c)
        ascii_val -= index
        new_c = chr(ascii_val)
        new_str += new_c
    return new_str

def main():
    if len(sys.argv) != 2:
        print "Missing argument"
        return
    print decrypt(sys.argv[1])

if __name__ == '__main__':
    main()
```

3) Ensuite nous avons juste a passer le contenu de `token` dans notre programme python

```bash
python /tmp/level09.py $(cat token)
f3iji1ju5yuevaus41q1afiuq
getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```
