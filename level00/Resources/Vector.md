- Identified and read files owned by user `flag00`

```
level00@SnowCrash:~$ find / -user flag00 2>/dev/null 
/usr/sbin/john
/rofs/usr/sbin/john
level00@SnowCrash:~$ cat /usr/sbin/john
cdiiddwpgswtgt
level00@SnowCrash:~$ cat /rofs/usr/sbin/john
cdiiddwpgswtgt
```

- Attempted decoding of `cdiiddwpgswtgt` using variations of ROT using cyberchef tool ROT13 brute force

- Found ROT11 had meaningful result of `nottoohardhere`

- Authenticated to machine using credentials `flag00:nottoohardhere`

 - Authentication successful, ran `getflag` command to retrieve flag

```
level00@SnowCrash:~$ su flag00
Password: 
Don't forget to launch getflag !
flag00@SnowCrash:~$ getflag
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
```

- Authenticate to level01 using token

```
flag00@SnowCrash:~$ su level01
Password: 
level01@SnowCrash:~$ 
```
