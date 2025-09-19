-  In the directory `/home/user/level09` there is a binary `level09` and a data file `token`

- On examining the binary it requires a second argument to be passed through which is then encoded. After we pass in the argument `aaaaaa` and `000000` it is evident that the binary accepts a string and then encodes the string by incrementing each position by its index value

```
level09@SnowCrash:~$ pwd
/home/user/level09
level09@SnowCrash:~$ ./level09 
You need to provied only one arg.
level09@SnowCrash:~$ ./level09 token
tpmhr
level09@SnowCrash:~$ ./level09 aaaaaa
abcdef
level09@SnowCrash:~$ ./level09 000000
012345
```

- We assume the token file contents are an encoded version of the token string required to get the flag

- On reading the token file, the characters appear to be non printable, and a hex dump confirms this.

```
level09@SnowCrash:~$ ls
level09  token
level09@SnowCrash:~$ cat token
f4kmm6p|=�p�n��DB�Du{��
level09@SnowCrash:~$ xxd token
0000000: 6634 6b6d 6d36 707c 3d82 7f70 826e 8382  
0000010: 4442 8344 757b 7f8c 890a                 f4kmm6p|=..p.n..DB.Du{....
```

- We prepare a python script which takes each hex value and decodes it by decrementing by its index value (except for the last value `0a`  which is the `null` terminator)

```
word = [
	0x66, 0x34, 0x6b, 0x6d, 0x6d, 0x36, 0x70, 0x7c,
	0x3d, 0x82, 0x7f, 0x70, 0x82, 0x6e, 0x83, 0x82,
	0x44, 0x42, 0x83, 0x44, 0x75, 0x7b, 0x7f, 0x8c,
	0x89 ]
	
def decrypt_word():
	count = len(word)
	i, j = 0, 0
	result = ""
	while (i < count):
		result += (chr((word[i] - j)% 256))
		i+=1
		j+=1
	print(result)

decrypt_word()
```

- Upon running the script the token is decoded

```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$  python3 script.py 
f3iji1ju5yuevaus41q1afiuq
```

- Authenticate as `fla09` using the decoded token to retrieve the flag

```
level09@SnowCrash:~$ su flag09
Password: 
Don't forget to launch getflag !
flag09@SnowCrash:~$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```

- Authenticate as `level10` using the token
```
flag09@SnowCrash:~$ su level10
Password: 
level10@SnowCrash:~$ 
```

