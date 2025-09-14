- Discovered .pcap file `/home/user/level02` and ex-filtrated to attack machine for analysis

```
level02@SnowCrash:~$ pwd
/home/user/level02
level02@SnowCrash:~$ ls
level02.pcap
level02@SnowCrash:~$ python -m SimpleHTTPServer 9999
Serving HTTP on 0.0.0.0 port 9999 ...
10.13.200.129 - - [18/Sep/2025 16:47:34] "GET /level02.pcap HTTP/1.1" 200 -
```

- Launched wireshark on attack machine with pcap file to analyze further

```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ sudo wireshark level02.pcap 
```

- Examining the TCP stream reveal a potential password however non printable characters are present by form of "." in ascii format

![[Pasted image 20250913225648.png]]

- Viewing as hexdump, the non printable characters are revealed as `7f` which equates to `delete` and `0d` which equates to `/cr`

![[Pasted image 20250913225829.png]]

- Retyping the potential password and removing the previous character everytime `7F` is encountered results in:
	`ft_waNDReL0L` 
	
- Authenticate as flag02 using the credentials `flag02:ft_waNDReL0L` and retrieve the flag

```
level02@SnowCrash:/var$ su flag02
Password: 
Don't forget to launch getflag !
flag02@SnowCrash:~$ getflag
Check flag.Here is your token : kooda2puivaav1idi4f57q8iq
```

- Authenticate to level03 using token
```
flag02@SnowCrash:~$ su level03
Password: 
level03@SnowCrash:~$ 
```