# Level 05

1) `ls` ne donne rien.

2) La commande `find / -user flag05`  trouve deux fichiers interresants

```bash
find / -user flag05
/usr/sbin/openarenaserver
/rofs/usr/sbin/openarenaserver
```

les deux fichiers contiennent le meme code source: 

```bash
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

3) ok donc ce que fait le script c'est qu'il accorde un temps cpu de 5s a un process, il execute un fichier puis le supprime. il suffit de lui faire executer `getflag` et c'est gagne

4) probleme on peut ecrire directement dans le dossier /opt/openarenaserver/ mais le script va lire le fichier puis le supprimer donc retour a la case depart pour trouver un moyen d'ecrire dans ce dossier sans suppresion

5) apres 1HHHHHH de recherche sans serrer du point y a ca qui trouve peut etre une solution: 

    - find / -name level05

ca trouve 2 fichier : 

    - /var/mail/level05
    - /rofs/var/mail/level05

les deux fichier contien la meme chose:
    - */2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05

6) apres un petit coup de cht gpt pour savoir ce que ca peut bien etre il s'agit en faite tout betement d'un cron qui tourne en boucle et qui toute les deux minute. 

7) pour choper le flag il faut faire en sorte d'utiliser le cron pour qu'il execute script avec un call a getflag, sachant que le script suprime sont fichier a la fin de c'es 5s. la solution ca serai d'avoir un doublon qui serait executer avec le premier mais pas supprimer

8) via un mini script on peut forcer la sortie a survivre grace a cron :

```bash
#!/bin/sh
getflag > /tmp/flag
```

cron a les droit de flag05, il appelle le script de lecture. Le script de lecture execute notre mini script avec les privileges de cron. Le resulat est sauvegarde dans le `/tmp`. le script de lecture suprimme notre mini script mais nous on garde le resultat.
