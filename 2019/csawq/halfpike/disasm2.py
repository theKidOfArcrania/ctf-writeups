data = open('chal.rom', 'rb').read()

offsets = list(range(0x400, 0x480, 0x20)) + list(range(0x500, 0x580, 0x20))

def dump_insn(data, offset, addr):
    x = data[offset+addr]
    y = data[offset+addr+1]
    print("  %02x: %s" % (addr, dump_insn_0(x >> 4, x & 0xf, y >> 4, y & 0xf)))

def dump_insn_0(a, b, c, d):
    if a == 0:
        return ("ASSERT_%s r%d, r%d" % (('NE', 'EQ')[d], b, c))
    elif a == 1:
        return ("ROL r%d, %d" % (b, c))
    elif a == 2:
        return ("MOV r%d, [%d]" % (b, c))
    elif a == 3:
        return ("XOR r%d, %d" % (b, c))
    elif a == 4:
        return ("MOV [%d], r%d" % (b, c))
    elif a == 5:
        return "JMP 0"
    elif a == 6:
        return "SKIPNE r%d, r%d" %(b, c)
    elif a == 7:
        return ("ADD r%d, %d" % (b, c))
    else:
        return "db %x %x %x %x" % (a, b, c, d)

for i, off in enumerate(offsets):
    print("State " + str(i))
    for pc in range(0, 0x20, 2):
        dump_insn(data, off, pc)
    print("")
    
