- Identified flag01 hash leak `42hDRfypTqqnw` in `/etc/passwd`

```
level00@SnowCrash:~$ cat /usr/sbin/john
cdiiddwpgswtgt
level00@SnowCrash:~$ cat /rofs/usr/sbin/john
cdiiddwpgswtgt
level00@SnowCrash:~$ su flag00
Password: 
Don't forget to launch getflag !
flag00@SnowCrash:~$ getflag
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
flag00@SnowCrash:~$ su level01
Password: 
level01@SnowCrash:~$ cat /etc/passwd
<snip>
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
<snip>
```

- Carried out hashcat cracking attempt on hash `42hDRfypTqqnw`
```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ echo '42hDRfypTqqnw' > hashfile                  
                                                                                                                     
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ hashcat hashfile /usr/share/wordlists/rockyou.txt
hashcat (v6.2.6) starting in autodetect mode

<snip>

42hDRfypTqqnw:abcdefg                                     
                                                          
Session..........: hashcat
Status...........: Cracked
Hash.Mode........: 1500 (descrypt, DES (Unix), Traditional DES)
Hash.Target......: 42hDRfypTqqnw

<snip>
```

- Hash cracked to reveal credential `abcdefg`

- Authenticated to flag01 using credentials `flag01:abcdefg` and retrieved flag01

```
level01@SnowCrash:~$ su flag01
Password: 
Don't forget to launch getflag !
flag01@SnowCrash:~$ getflag
Check flag.Here is your token : f2av5il02puano7naaf6adaaf
```

- Authenticated to level02 using token

```
flag01@SnowCrash:~$ su level02
Password: 
level02@SnowCrash:~$ 
```

