1) bon le debut et facile, un simple ls permet de voir qu'il y a un fichier level02.pcap

2) les fichier .pcap ce sont des enregistrement de flux reseau. l'outil le plus pratique sous linux pour le lire (merci la vm) c'est wireshark car il est graphique

3) quand on retrace toute la convercation byte par byte du flux tcp on obtien ca :

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


4) on peut voir le mdp en clair mais les si on regarde dans wireshark, les bytes de "." corresponde en realiter a des white space. directement dans wireshark on peut changer la table ascii par les code en C et ca donne ca :

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

6) on a le meme mdp en format 0xXX, et on peut voir que chaque byte de "." (0x7f) correspond en realiter a "del" en ascii. l'utilisateur a donc fait des retour arriere dans sont mots de passe, on passe donc de :
    - ft_wandr...NDRel.L0L
    - ft_waNDReL0L

7) plus qu'as ce connecter a la session flag02