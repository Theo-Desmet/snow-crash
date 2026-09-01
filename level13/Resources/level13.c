#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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

void main(void)
{
  uid_t uid;
  char *buff;

  uid = getuid();
  if (uid != 4242)
  {
    uid = getuid();
    printf("UID %d started us but we we expect %d\n", uid, 4242);
    exit(1);
  }
  buff = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
  printf("your token is %s\n", buff);
}
