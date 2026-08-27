comment trouver le flag: 

1) la session level00 n'a rien d'interresant
2) chercher si on peut trouver des fichier/dossier associer a flag00
3) find / -user flag00
4) on trouve deux fichier sans restriction de permition :
    - /usr/sbin/john
    - /rofs/usr/sbin/john
5) les deux fichier contienne la meme chaine de caractere:
    - cdiiddwpgswtgt
6) le code trouver ne fonctionne pas comme mot de pass a la session flag00
7) si on fait un dechiffrage cesar avec un decalage de 15 on trouve

    - nottoohardhere
    
8) deja envie de crever mais au moins ca marche on peut ce connecter a flag00