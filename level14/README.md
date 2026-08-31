# Level 14

1) Les commande `ls` et `find` ne permet pas de trouver quoi que ce soit d'utile pour ce dernier bonus

2) en regardant plus attentivement on ce rend compte que l'on peut directement decompiler `getflag` dans ghidra ce qui donne remis en C le fichier en resources getflag.c

3) en lissant bien le code on ce rend compte qu'il est assez simple dans les grande ligne il ce separe en 2 etat importante : 

```c
_Var6 = getuid();
```

le programme check notre user id

```c
else if (_Var6 == 0xbc5) {
    pcVar4 = (char *)ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
    fputs(pcVar4,__stream);
}
```

si notre user id correspond au flag souhaiter alors une fonction de decryptage et appeler pour donner le flag

4) on peut soit chercher a brutforce ft_des, soit s'inspirer de la methode precedente avec gdb pour passer. c'est la deuxieme option que l'on a choisit.

```bash
cat /etc/passwd
```
```
level00:x:2000:2000::/home/user/level00:/bin/bash
level01:x:2001:2001::/home/user/level01:/bin/bash
level02:x:2002:2002::/home/user/level02:/bin/bash
level03:x:2003:2003::/home/user/level03:/bin/bash
level04:x:2004:2004::/home/user/level04:/bin/bash
level05:x:2005:2005::/home/user/level05:/bin/bash
level06:x:2006:2006::/home/user/level06:/bin/bash
level07:x:2007:2007::/home/user/level07:/bin/bash
level08:x:2008:2008::/home/user/level08:/bin/bash
level09:x:2009:2009::/home/user/level09:/bin/bash
level10:x:2010:2010::/home/user/level10:/bin/bash
level11:x:2011:2011::/home/user/level11:/bin/bash
level12:x:2012:2012::/home/user/level12:/bin/bash
level13:x:2013:2013::/home/user/level13:/bin/bash
level14:x:2014:2014::/home/user/level14:/bin/bash
flag00:x:3000:3000::/home/flag/flag00:/bin/bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
flag02:x:3002:3002::/home/flag/flag02:/bin/bash
flag03:x:3003:3003::/home/flag/flag03:/bin/bash
flag04:x:3004:3004::/home/flag/flag04:/bin/bash
flag05:x:3005:3005::/home/flag/flag05:/bin/bash
flag06:x:3006:3006::/home/flag/flag06:/bin/bash
flag07:x:3007:3007::/home/flag/flag07:/bin/bash
flag08:x:3008:3008::/home/flag/flag08:/bin/bash
flag09:x:3009:3009::/home/flag/flag09:/bin/bash
flag10:x:3010:3010::/home/flag/flag10:/bin/bash
flag11:x:3011:3011::/home/flag/flag11:/bin/bash
flag12:x:3012:3012::/home/flag/flag12:/bin/bash
flag13:x:3013:3013::/home/flag/flag13:/bin/bash
flag14:x:3014:3014::/home/flag/flag14:/bin/bash

```
on reprend la methode de l'exo 01, oui ca remonte deja mais ca nous permet de retrouver la valeur du userid du flag14 qui est de `3014`.

5) en desassemblent dans gdb getflag on peut peut voir a quel endrot ce fait le call a `getuid` et surtout que le retour de `getuid` ce fait dans le registre `eax` : 

```
   (gdb) disas main

    [...]

   0x08048afd <+439>:	call   0x80484b0 <getuid@plt>
   0x08048b02 <+444>:	mov    %eax,0x18(%esp)
```

6) il suffit donc dans gdb d'intercepter le resultat de `getuid` et de remplacer sont resultat `2014` par celui du user flag14 `3014`. cependant il reste encore une bariere a passer avant cela. il y a une protection mis en place exactement pour empecher ce que l'on essaie de faire: `ptrace` est attacher au programe getflag, donc lorsque nous executons getflag depuis gdb cela permet au programme que l'on le lance depuis un debugeur et de ce couper avant toute modification. cependant il est aussi possible de casser cette securiter. en dessasemblant le code on peut voir ca : 

```
(gdb) disas main
Dump of assembler code for function main:
	 [...]
   0x08048989 <+67>:	call   0x8048540 <ptrace@plt>
   0x0804898e <+72>:	test   %eax,%eax
   [...]
```

7) donc si on reunis toute les infos precedente on doit aller a +72 faire sauter la securiter de `ptrace` puis aller en +444 modifier le retour de `getuid` afin de ce faire passer pour l'utlisateur flag14 au yeux de getflag dans cette instance de gdb ce qui donne :

```
(gdb) b *main+72
Breakpoint 1 at 0x804898e
(gdb) r
Starting program: /bin/getflag 

Breakpoint 1, 0x0804898e in main ()
(gdb) set $eax=0
(gdb) b *main+444
Breakpoint 2 at 0x8048b02
(gdb) c
Continuing.

Breakpoint 2, 0x08048b02 in main ()
(gdb) info registers
eax            0x7de	2014
ecx            0xb7fda000	-1208115200
edx            0x20	32
ebx            0xb7fd0ff4	-1208152076
esp            0xbffff630	0xbffff630
ebp            0xbffff758	0xbffff758
esi            0x0	0
edi            0x0	0
eip            0x8048b02	0x8048b02 <main+444>
eflags         0x200246	[ PF ZF IF ID ]
cs             0x73	115
ss             0x7b	123
ds             0x7b	123
es             0x7b	123
fs             0x0	0
gs             0x33	51
(gdb) set $eax=3014
(gdb) c
Continuing.
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
[Inferior 1 (process 2450) exited normally]

```
8) petit bonus cette methode permet de casser tout les flag precedent du projet, marrant si a la corection on utiliser que ca pour tout les flags :)