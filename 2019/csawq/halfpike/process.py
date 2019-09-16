import sys

f = open(sys.argv[1], 'r')

insns = {}
for line in f:
    addr, _, insn = line.strip().partition(': ')
    addr = int(addr, 16)
    if addr in insns:
        if insns[addr] != insn:
            print("WARNING: self-modifying code!")
    insns[addr] = insn

addrs = list(insns)
addrs.sort()
for addr in addrs:
    print("%08x: %s" % (addr, insns[addr]))
    
    
