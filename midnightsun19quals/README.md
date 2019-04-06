# Midnightsun CTF Writeups

Midnight sun was a very fun and challenging CTF, and all in all, we got 1st
place as team dcua. 

Though I submitted all of these chal flags and wrote most of the exploit code
for it, I would definitely like to give much credit to @jitterbug\_gang and
others for finding the initial leak and bug for gissa, as I would've taken
probably much longer searching for it to find it :) (I was also seriously
considering to brute 24 bits of ASLR it to solve it...)

I also told myself if I repeated the same mistakes I've made in this CTF and
others, I'd probably be fired 'cause I made so many of 'em that cost a whole lot
of time, (though I'd also probably be rehired immediately thereafter, because
I would be the only one to understand the code :P )

## hfs-mbr
Look at readme for setup on debugger. 

Essentially the MBR is reading in 9 characters, (keeping track of the current
index of character), and checking the character is in the right position, using
some simple assembly logic. If all 9 are in right position, authenticate,

password: sojupwner

## hfs-dos
We can go out of bounds and overwrite other data if we send a lot of backspaces
(`\x7f`). So just overwrite two places: set `FLAG1` to `FLAG2` to print second
flag, and then set the jump table of commands to point to the show flag
function. See `hfs-dos.py` for exploit code.

## gissa2
First we set size of buffer to some large number by entering empty string. Then
overwrite buffer length to exactly right before the return address, to leak PIE.
Then send a ORW ROP chain, except use x32 open syscall to bypass seccomp rules. 
See `gissa.py` for more details.

## hfs-vm1/2
I rigged up a quick [compiler][1] to help in the VM bytecode writing process. It
uses a gcc backend :P so it has full builtin support for C-style comments,
simple arithmetic expressions, etc...

First part was easy, and it simply consisted of:
```
BEGIN_VM
  MOVI(R_SP, 0)
  MOVI(R_SYS, SYS_LS)
  DEBUG()
  SYSCALL()

  MOVI(R_SYS, SYS_FLAG)
  SYSCALL()

  MOVI(R_SYS, SYS_WRITE)
  SYSCALL()
END_VM
```

Second part was a bit more tricky, so I will break down into multiple stages:

1. Leak return address on user side, so that we can de-ASLR the PIE.
2. Pivot the stack on user side to a known bss address. 
3. Using an unchecked set stack indirect, do a slow ROP thing so that we get
   arbitrary code exec on user side.
3. Using write to socket, we exploit a race condition in the `SYS_random`
   syscall whenever the 1st argument is passed the value 4, and then rapidly set
   the shared memory to a larger size, so that during writeback, the kernel will
   leak its special stack cookie for us to use.
4. Finally, using stack cookie, buffer overflow parent process and ROP to
   `system('/bin/sh')`. 

See `hfs-vm2.py` for a complete PoC.

[1]: https://bit.ly/2G3D67g
