1) un coup de ls et on a immediatemente un petit level04.pl. on vas donc commencer a casser su perl...trop hate...

2) le code ressemble a ca :

#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));

et quand on l'execute on a juste comme messaje de sortie :
    - Content-type: text/html



3) pwouaaaa, ca synthaxe de puant. en gros, ce que fait le programme, il import param, param lis sur le port 4747 qui est ouvert. ce qui est lu est envoyer comme argument a la fonction x (vraiment faut le bruler vif le mec qui a choisit ce nom de fonction). c'est stocker dans la variale $y. et enfin la giga fail de securiter. le print va executer en bash ce qu'un lui donne et afficher le resultat avec echo... donc en gros le seul truc que fait ce code c'est etre une fail de securiter qui lis les input de l'utilisateur et les execute en bash directement et sans restriction de permision... pas mal

4) bref tout ca pour dire qu'il suffit de mettre getflag sur le port 4747 pour que le programme perl le lance pour nous et donne le resultat:
    - curl 'localhost:4747/?x=$(getflag)'

