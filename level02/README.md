# Level 02

1) Ici, un simple `ls` permet de voir qu'il y a un fichier `level02.pcap`

```bash
ls -la
total 24
dr-x------ 1 level02 level02  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level02 level02  220 Apr  3  2012 .bash_logout
-r-x------ 1 level02 level02 3518 Aug 30  2015 .bashrc
----r--r-- 1 flag02  level02 8302 Aug 30  2015 level02.pcap
-r-x------ 1 level02 level02  675 Apr  3  2012 .profile
```

2) Les fichier `.pcap` sont des enregistrements de flux reseau. L'outil le plus pratique sous linux pour le lire est `wireshark`.

3) quand on retrace toute la conversation byte par byte du flux tcp on obtient ceci :

```
..%
..%
..&..... ..#..'..$
..&..... ..#..'..$
.. .....#.....'.........
.. .38400,38400....#.SodaCan:0....'..DISPLAY.SodaCan:0......xterm..
........"........!
........"..".....b........b....	B.
..............................1.......!
.."....
.."....
..!..........."
........"
..".............	..
.....................
Linux 2.6.38-8-generic-pae (::ffff:10.1.1.2) (pts/10)

..wwwbugs login: 
l
.l
e
.e
v
.v
e
.e
l
.l
X
.X


..
Password: 
ft_wandr...NDRel.L0L

.
..
Login incorrect
wwwbugs login: 
```

4) on peut voir le mdp en clair mais les si on regarde dans `wireshark`, les bytes de "." correspondent en realite a des whitespaces. Directement dans `wireshark` on peut changer la table ascii par les codes en C et ca donne ceci :

```C
char peer0_13[] = { /* Packet 45 */
0x66 };
char peer0_14[] = { /* Packet 47 */
0x74 };
char peer0_15[] = { /* Packet 49 */
0x5f };
char peer0_16[] = { /* Packet 51 */
0x77 };
char peer0_17[] = { /* Packet 53 */
0x61 };
char peer0_18[] = { /* Packet 55 */
0x6e };
char peer0_19[] = { /* Packet 57 */
0x64 };
char peer0_20[] = { /* Packet 59 */
0x72 };
char peer0_21[] = { /* Packet 61 */
0x7f };
char peer0_22[] = { /* Packet 63 */
0x7f };
char peer0_23[] = { /* Packet 65 */
0x7f };
char peer0_24[] = { /* Packet 67 */
0x4e };
char peer0_25[] = { /* Packet 69 */
0x44 };
char peer0_26[] = { /* Packet 71 */
0x52 };
char peer0_27[] = { /* Packet 73 */
0x65 };
char peer0_28[] = { /* Packet 75 */
0x6c };
char peer0_29[] = { /* Packet 77 */
0x7f };
char peer0_30[] = { /* Packet 79 */
0x4c };
char peer0_31[] = { /* Packet 81 */
0x30 };
char peer0_32[] = { /* Packet 83 */
0x4c };
char peer0_33[] = { /* Packet 85 */
0x0d };
```

6) On a le meme mdp en format hexadecimal, et on peut voir que chaque `.` correspond en realite a `del` en ascii. L'utilisateur a donc fait des retours arriere dans sont mot de passe, on passe donc de :
    - ft_wandr...NDRel.L0L
    - ft_waNDReL0L
