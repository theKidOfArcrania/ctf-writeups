import sys
import mmap

with open("elf2.patch.bin", "rw+b") as f:
    mm = mmap.mmap(f.fileno(), 0)
    for line in sys.stdin:
        inp = line[:-1].split(' ')
        if eval(inp[0])[0] == '\xcc':
            continue
        
        data = eval(inp[0])
        off = eval(inp[1]) - 0x555555554000
        mm[off:off+len(data)] = data
    mm.close()


