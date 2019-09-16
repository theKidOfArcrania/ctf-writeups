from lab3_values import values
from struct import pack
from binascii import hexlify

def mix(x):
    return (x + ((x >> 5)^(x<<4))) & 0xffffffff

fn     = 0x57415343
fprev  = 0x41484148

#fprev  = 0x57415343
#fn     = 0x41484148

for x in values[::-1]:
    tmp = (fn + (mix(fprev) ^ x)) & 0xffffffff
    fn = fprev
    fprev = tmp

#print("a[0:4] = {}; a[4:8] = {}".format(fn, fprev))
print(hex(fn)[2:] + '-' + hex(fprev)[2:])

