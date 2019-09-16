import logging
import itertools

import angr
import claripy


p = angr.Project('silkroad.elf')
p.hook(0x408F10, angr.SIM_PROCEDURES['libc']['strlen']())

s = p.factory.blank_state(addr=0x40140a)

concrete_addr = 0xffe00000
iden = claripy.BVS('iden', 13*8)

s.memory.store(concrete_addr, iden)
s.regs.rdi = concrete_addr

s.add_constraints(iden.get_byte(9) == 0)
s.add_constraints(iden.get_byte(10) == 0)
s.add_constraints(iden.get_byte(11) == 0)
s.add_constraints(iden.get_byte(12) == 0)

for i in range(9):
    s.add_constraints(iden.get_byte(i) <= 0x39)

sm = p.factory.simulation_manager(s)

#sm.explore(find=0x4017b9, avoid=0x4017C0)
