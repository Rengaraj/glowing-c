glowing-c
=========

For writing some application using c

## My Shell or Mini Shell

This is a shell implimentation written initially by Vijaykumar B.
It was send to mailing list of Embedded Linux Meetup group chennai.
Following are the features planned to add on top of this code.

 * I/O redirection command to redirect command output to a file.
 * Pipeline implimentation.
 * Setting environment and that can be used by a command.

## Download and Compiling the code

```
$ git clone https://github.com/gnurenga/glowing-c.git
$ cd glowing-c/trunk
$ gcc mshell.c -o mshell
```

## Runing mshell
* Run the compiled mshell

```
$ ./mshell
/home/user/project/glowing-c/trunk$ h
c: Change Directory
f: Execute Command
x: Exit
i: I/O redirection
h: Help
/home/user/project/glowing-c/trunk$ f
cmd: ps
PID TTY          TIME CMD
5720 pts/4    00:00:00 bash
5734 pts/4    00:00:00 mshell
5736 pts/4    00:00:00 ps
/home/user/project/glowing-c/trunk$
```

## Testing I/O redirection with mshell

```
/home/user/project/glowing-c/trunk$ i
cmd: ls
filename: new.txt
/home/user/project/glowing-c/trunk$ f
cmd: cat new.txt
mshell
mshell.c
new.txt
singley.c
test.c

```