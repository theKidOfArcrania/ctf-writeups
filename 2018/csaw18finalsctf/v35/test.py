from z3 import *
import numpy as np
from lab3_values import values as data
 
#data = np.genfromtxt("xor-values.txt", str, delimiter=",")

data = [1,2,3,4,5]

def r_dec( _reg, _ebx, _esi, i ):
    _reg -= _ebx
    _ebx = _reg
    _esi = _reg
    _esi = LShR(_esi, 5)
    _ebx <<= 4
    _ebx ^= _esi
    _ebx += _reg
    _ebx ^= data[i]
    return _reg, _ebx, _esi
 
edx = BitVec('edx',32)
esi = BitVec('esi',32)
 
i = 0
eax = edx
ebx = edx
ebx =  LShR(ebx, 5)
eax <<= 4
eax ^= ebx
eax += edx
eax ^= data[i]
i += 1
esi -= eax
ebx = esi
eax = esi
esi = LShR(esi, 5)
ebx <<= 4
ebx ^= esi
ebx += eax
ebx ^= data[i]
i += 1
while i < len(data)-2 :
    edx, ebx, esi = r_dec(edx, ebx, esi, i)
    eax, ebx, esi = r_dec(eax, ebx, esi, i+1)
    i += 2
edx, ebx, esi = r_dec(edx, ebx, esi, i)
eax -= ebx
ebx = eax
esi = eax
esi = LShR(esi, 5)
ebx <<= 4
ebx ^= esi
ebx += eax
ebx ^= 0xdeadbeef
edx -= ebx
 
s = Solver()
s.add(And(eax == 0x57415343, edx == 0x41484148))
print(s.check())
print(s.model())
