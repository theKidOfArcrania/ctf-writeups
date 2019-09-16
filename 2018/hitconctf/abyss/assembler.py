#!/usr/bin/python
import sys
from pwn import *

insts = {'DUP': '$', 'POP': '%', 'AND': '&', 'MUL': '*', 'ADD': '+', 'WRITE':
        ',', 'MINUS': '-', 'WRITED': '.', 'DIV': '/', 'STORE':':', 'FETCH':';',
        'EQ':'=', 'GT':'>', 'ROT': '@', 'SWAP': '\\', 'NEG': '_', 'OR': '|',
        'NOT': '~'}

def error(line, linenum, msg):
    print("ERROR on line %d: %s:\n  %s" % (linenum, msg, line))

def to_dwords(s):
    s += '\0' * (4 - len(s) % 4)
    nums = []
    for i in range(0, len(s), 4):
        nums += [u32(s[i:i+4])]
    return nums

def assemble(fname):
    linenum = 0
    f = open(fname, "r")
    code = ''
    asmmode = False
    asmcode = ''
    for l in f:
        linenum += 1
        ll = l.split('#')[0].strip().upper()
        if asmmode:
            if ll == 'ENDASM':
                nums = to_dwords(asm(asmcode, arch='x86_64'))
                code += '`'.join(map(str, nums)) + '`'
                code += insts['POP'] * len(nums)
                asmmode = False
            else:
                asmcode += l.split('#')[0].strip() + '\n'
            continue
        if ll == '':
            continue
        elif ll[0] in '0123456789':
            try:
                code += str(int(ll)) + '`'
            except:
                error(l, linenum, "Invalid number")
        elif ll == 'ASM':
            asmmode = True
        else:
            if ll in insts:
                code += insts[ll]
            else:
                error(l, linenum, "Invalid instruction")
    if asmmode:
        error('', linenum, "Expected 'ENDASM'")
    return code

def main():
    if len(sys.argv) != 2:
        print("Usage: %s <file>" % sys.argv[0])
        exit(1)
    print(assemble(sys.argv[1]))

if __name__ == '__main__':
    main()

