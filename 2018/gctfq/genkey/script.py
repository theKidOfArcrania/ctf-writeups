from pwn import *

def getCheck(iden):
    hasher = "ltrace ./exec2 ./elf2.patch.bin %s %s 2>&1 > /dev/null | grep strcmp | sed 's/.*\.\.\.\, //' | sed 's/...) = .*//'"
    h = process(hasher % (iden, 'f' * 32), shell=True)
    line = h.recvline()[1:][:-2]
    h.close()
    return line

def sendAnswer(p):
    from binascii import hexlify, unhexlify 

    iden = p.recvline()[:-1]
    print("Checking for %s" % iden)
    inp = unhexlify(getCheck(iden))
    data = [ord(inp[i]) ^ (i | i << 4) for i in range(len(inp))]
    data = [chr(data[i] & 0xf | data[0xf - i] & 0xf0) for i in range(len(inp))]
    data = ''.join(data)
    p.sendline(hexlify(data))
    p.recvuntil("OK")
    p.recvline()
    print("Success!")


p = remote('keygenme.ctfcompetition.com', 1337)
while True:
    sendAnswer(p)
