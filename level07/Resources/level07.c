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
