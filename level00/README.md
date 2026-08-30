# Level 01

1) la session `level00` n'a rien d'interessant
2) chercher si on peut trouver des fichiers/dossiers associes a `flag00`

```bash
find / -user flag00 2>/dev/null
```

3) on trouve deux fichiers sans restrictions de permissions :
    - /usr/sbin/john
    - /rofs/usr/sbin/john
    
4) les deux fichier contiennent la meme chaine de caractere:
    - cdiiddwpgswtgt
    
5) le code trouve ne fonctionne pas comme mot de passe a la session `flag00`

6) si on fait un dechiffrage cesar avec un decalage de 15 on trouve
    - nottoohardhere

```bash
find / -user flag00 2>/dev/null
/usr/sbin/john
/rofs/usr/sbin/john
cat /usr/sbin/john
cdiiddwpgswtgt # nottoohardhere
```
