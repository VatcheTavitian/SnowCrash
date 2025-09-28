# SnowCrash
42 Snow Crash PenTesting Project

As part of Ecole 42's cybersecurity track, this project's aim is to capture 14 flags in the snowcrash.iso (snowcrash.iso not published in repo)

Most of the levels require understanding and exploiting vulnerabilities in the binaries & scripts presented in the users' home folder. Each level has its own user home folder.
In cases where no binary or script is present, you need to exercise your enumeration skills to find the clue which will lead to getting the flag.

Basic Start:

Launch snowcrash.iso in a virtual machine. The IP address of machine is shown.

The user starts with credentials `level00:level00`
On attack host ssh into the snowcrash machine to port 4242
`ssh -p 4242 level00@<SnowCrashIP>`

Once a clue or token is found switch user to the corresponding flag user eg `su flag00` or `su flag01` etc... and enter the found clue/token/credential to authenticate.

Once authenticated as flagXX run `getflag` command to retrieve the flag.

The flag is the password to authenticate to the next level so then `su level<number of next level>` and repeat the process until level14/flag14 is obtained.
