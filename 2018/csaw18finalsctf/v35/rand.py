#!/usr/bin/python3

from Crypto.Util.number import inverse

def rand(seed):
    return (seed * 1664525 + 1013904223) & 0xffffffff

def rand_inv(value):
    return ((value - 1013904223) * inverse(1664525, 2**32)) & 0xffffffff

def read_rand():
    rand = 0
    robots = list(map(int, raw_input("Robots that you see: ").split(' ')))
    assert len(robots) == 8
    for i in range(len(robots)):
        assert (robots[i] & 0xf) == robots[i]
        rand |= robots[i] << (i*4)
    
    print("random is: {:08x}".format(rand))
    return rand

assert rand_inv(rand(23)) == 23

r = read_rand()
#r2 = read_rand()

#assert(rand(r) == r2)

rinv = rand_inv(r)
print("Code starts at ASLR {:04x}".format((rinv & 0xfff) + 0x8014))
print("Cookie is {:08x}".format(rand_inv(rinv)))
