- After much enumeration as user `level14` we turn our attention to the actual binary `getflag` and ex-filtrate it the attack machine to examine the source code.

- On de-compilation and examination we find the binary uses the same `ft_des()` function we found in level13 in order to decrypt and reveal the token for the user `flag14` with UID 0xbc6 (3014)

```
level14@SnowCrash:~$ id flag14
uid=3014(flag14)
```

![[Pasted image 20250922181906.png]]

- We then use the same script from level13 to decrypt the obtained string `g <t61:|4_|!@IF.-62FH&G~DCK/Ekrvvdwz?v|` , which we place in the `main` function of the script

```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ tail -n5 ft_des_decrypt_script.c
int main() {
 printf(ft_des("g <t61:|4_|!@IF.-62FH&G~DCK/Ekrvvdwz?v|"));

                 return(0);
}

```

- Compile and run the binary to reveal the token
```
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ cc ft_des_decrypt_script.c -o ft_des_decrypt_script    
┌──(kali㉿kali)-[~/Desktop/snowcrash]
└─$ ./ft_des_decrypt_script 
7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ   
```

- Authenticate to `flag14` using the token and obtain the flag

```
level14@SnowCrash:/bin$ su flag14
Password: 
Congratulation. Type getflag to get the key and send it to me the owner of this livecd :)
flag14@SnowCrash:~$ getflag
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```


