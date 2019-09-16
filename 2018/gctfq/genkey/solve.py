#!/usr/bin/python3

import sys


from binascii import hexlify, unhexlify

inp = unhexlify(input("Solve for: "))

data = [inp[i] ^ (i | i << 4) for i in range(len(inp))]
data = [data[i] & 0xf | data[0xf - i] & 0xf0 for i in range(len(inp))]
print(hexlify(bytes(data)))



