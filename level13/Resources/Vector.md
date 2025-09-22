- In the directory `/home/user/level13` we see the binary `level13` with SUID `flag13`. The file when executed expects the user with UID 4242

```
level13@SnowCrash:~$ ls -la
total 20
dr-x------ 1 level13 level13  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level13 level13  220 Apr  3  2012 .bash_logout
-r-x------ 1 level13 level13 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag13  level13 7303 Aug 30  2015 level13
-r-x------ 1 level13 level13  675 Apr  3  2012 .profile
level13@SnowCrash:~$ file level13 
level13: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xde91cfbf70ca6632d7e4122f8210985dea778605, not stripped
level13@SnowCrash:~$ ./level13 
UID 2013 started us but we we expect 4242
level13@SnowCrash:~$ id
uid=2013(level13) gid=2013(level13) groups=2013(level13),100(users)
```

- On ex-filtration and de-compilation of the code into `ghidra` we find the main expects  UID 4242 in order to decrypt a string using function `ft_des()` and return a token
- 
![[Pasted image 20250922164430.png]]

- On clicking `ft_des()` we see the decryption function for the string
```
char * ft_des(char *param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  byte bVar5;
  uint local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  bVar5 = 0;
  pcVar2 = strdup(param_1);
  local_1c = 0;
  local_20 = 0;
  do {
    uVar3 = 0xffffffff;
    pcVar4 = pcVar2;
    do {
...
<snip>
```

- We take the `ft_des()` function and prepare a decryption script found in this repo's level13 resouces folder called `ft_des_decrypt_script` where we pass into the function the string to decrypt from the main decompiler `ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");`

- Compile the script into a binary and run to retrieve the token
- 
```
┌──(kali㉿kali)-[~/Desktop/SnowCrash]
└─$ cc ft_des_decrypt_script.c -o ft_des_decrypt_script
                                                                                                                   
┌──(kali㉿kali)-[~/Desktop/SnowCrash]
└─$ ./ft_des_decrypt_script                            
2A31L79asukciNyi8uppkEuSx 
```

- Use the token to authenticate to `level14` as the token doesn't authenticate as `flag13`.

```
level13@SnowCrash:~$ su flag13
Password: 
su: Authentication failure
level13@SnowCrash:~$ su level14
Password: 
level14@SnowCrash:~$ 

```

------------------------------------------------------
Note - Alternatively you can change the parameter value in the assembly code to UID 4242 and recompile the program to get the token

- In main decompiler locate and highlight the variable `_Var1 = getuid()`You will see the corresponding assembler code. Right click on the assembler code and select `Patch Instruction`

![[Pasted image 20250922170819.png]]


- Change the values to `MOV` and `EAX, 0x1092` to set the variable `_Var1` to uid 4242

![[Pasted image 20250922171743.png]]

- Export the program by selecting `File > Export Program` and set format `Original File` . Set the output filename to `modified` in whatever location you like.

- Set the file permissions to executable and run the program the obtain the flag.

```
┌──(kali㉿kali)-[~/Desktop]
└─$ sudo chmod +x modified
[sudo] password for kali: 
                                                                                                                   
┌──(kali㉿kali)-[~/Desktop]
└─$ ./modified            
your token is 2A31L79asukciNyi8uppkEuSx


```

