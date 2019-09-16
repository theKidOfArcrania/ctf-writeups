
def get_inc_text8():
    global pc, pc_off, code

    b = code[pc - pc_off]
    pc += 1
    return b

def get_inc_text16():
    return get_inc_text8() | get_inc_text8() << 8

def get_inc_text32():
    return get_inc_text8() | get_inc_text8() << 8 | get_inc_text8() << 16 \
            | get_inc_text8() << 24

def top(a):
    return (a >> 4) & 0xf

def bot(a):
    return a & 0xf



def main():
    global pc, pc_off, code
    
    from code import code
    #code = open('code.vm', 'rb').read()

    insts = {}
    pc_off = 0x4000

    queue = [0x4000]
    while len(queue) != 0:
        pc = queue.pop()
        while True:
            cur_pc = pc
            if cur_pc in insts:
                break
            if cur_pc - pc_off >= len(code):
                break

            inst, queued = read_inst()
            insts[cur_pc] = inst

            if queued and queued not in insts:
                queue.append(cur_pc)
                queue.append(pc)
                break

    addrs = list(insts.keys())
    addrs.sort()
    for a in addrs:
        print(f'{a:04x}: {insts[a]}')


def read_inst():
    global pc, pc_off, code

    opc = get_inc_text8()
    if opc == 0:
        return 'nop', None
    elif opc == 1:
        return f'sub sp, 0x{get_inc_text8():02x}', None
    elif opc == 2:
        b = get_inc_text8()
        return f'mov r{bot(b)}, r{top(b)}', None
    elif opc == 3:
        b = get_inc_text8()
        return f'mov byte [sp + r{bot(b)}], r{top(b)}', None
    elif opc == 4:
        b = get_inc_text8()
        return f'mov r{bot(b)}, byte [r{top(b)}]', None
    elif opc == 5:
        b = get_inc_text8()
        addr = get_inc_text16()
        return f'bz r{top(b)}, off_{addr:04x}', addr
    elif opc == 6:
        return f'ret', None
    elif opc == 7:
        b = get_inc_text8()
        return f'mov r{bot(b)}, dword [r{top(b)}]', None
    elif opc == 8:
        b = get_inc_text8()
        return f'sysread [sp + r{bot(b)}], len=r{top(b)}', None
    elif opc == 9:
        b = get_inc_text8()
        return f'shr r{bot(b)}, r{top(b)}', None
    elif opc == 10:
        b = get_inc_text8()
        return f'mov dword [r{bot(b)}], r{top(b)}', None
    elif opc == 11:
        b = get_inc_text8()
        return f'syswrite [r{bot(b)}], len=r{top(b)}', None
    elif opc == 12:
        b = get_inc_text8()
        return f'xor r{bot(b)}, r{top(b)}', None
    elif opc == 13:
        b = get_inc_text8()
        t2 = top(get_inc_text8())
        return f'mov byte arr<r{bot(b)}>[r{t2}], r{top(b)}', None
    elif opc == 14:
        b = get_inc_text8()
        t2 = top(get_inc_text8())
        return f'mov r{bot(b)}, dword arr<r{top(b)}>[r{t2}]', None
    elif opc == 15:
        b = get_inc_text8()
        t2 = top(get_inc_text8())
        return f'mov word arr<r{bot(b)}>[r{t2}], r{top(b)}', None
    elif opc == 16:
        b = get_inc_text8()
        return f'mov dword [sp + r{bot(b)}], r{top(b)}', None
    elif opc == 17:
        b = get_inc_text8()
        return f'alloc_word r{top(b)}', None
    elif opc == 18:
        b = get_inc_text8()
        return f'sub r{bot(b)}, r{top(b)}', None
    elif opc == 19:
        b = get_inc_text8()
        t2 = top(get_inc_text8())
        return f'mov dword arr<r{bot(b)}>[r{t2}], r{top(b)}', None
    elif opc == 20:
        b = get_inc_text8()
        return f'mov r{bot(b)}, byte [sp + r{top(b)}]', None
    elif opc == 21:
        b = get_inc_text8()
        return f'free r{top(b)}', None
    elif opc == 22:
        b = get_inc_text8()
        return f'add sp, 0x{b:02x}', None
    elif opc == 23:
        b = get_inc_text8()
        return f'mov byte [r{bot(b)}], r{top(b)}', None
    elif opc == 24:
        addr = get_inc_text16()
        return f'call off_{addr:04x}', addr
    elif opc == 25:
        b = get_inc_text8()
        return f'syswrite [sp + r{bot(b)}], len=r{top(b)}', None
    elif opc == 26:
        b = get_inc_text8()
        return f'and r{bot(b)}, r{top(b)}', None
    elif opc == 27:
        b = get_inc_text8()
        addr = get_inc_text16()
        return f'bnz r{top(b)}, off_{addr:04x}', addr
    elif opc == 28:
        b = get_inc_text8()
        t2 = top(get_inc_text8())
        return f'mov r{bot(b)}, byte arr<r{top(b)}>[r{t2}]', None
    elif opc == 29:
        b = get_inc_text8()
        return f'shl r{bot(b)}, r{top(b)}', None
    elif opc == 30:
        b = get_inc_text8()
        return f'div [r{bot(b)}], r{top(b)}', None
    elif opc == 31:
        b = get_inc_text8()
        return f'sysexit {b}', None
    elif opc == 32:
        b = get_inc_text8()
        t2 = top(get_inc_text8())
        return f'mov r{bot(b)}, word arr<r{top(b)}>[r{t2}]', None
    elif opc == 33:
        b = get_inc_text8()
        return f'add r{bot(b)}, r{top(b)}', None
    elif opc == 34:
        b = get_inc_text8()
        return f'or r{bot(b)}, r{top(b)}', None
    elif opc == 35:
        b = get_inc_text8()
        return f'mov r{bot(b)}, dword [sp + r{top(b)}]', None
    elif opc == 36:
        b = get_inc_text8()
        return f'alloc_dword r{top(b)}', None
    elif opc == 37:
        addr = get_inc_text16()
        p = addr
        return f'jmp off_{addr:04x}', None
    elif opc == 38:
        b = get_inc_text8()
        return f'mult r{bot(b)}, r{top(b)}', None
    elif opc == 39:
        b = get_inc_text8()
        return f'alloc_byte r{top(b)}', None
    elif opc == 40:
        b = get_inc_text8()
        return f'sysread [r{bot(b)}], len=r{top(b)}', None
    elif opc == 41:
        b = get_inc_text8()
        return f'mov r{bot(b)}, 0x{get_inc_text32():08x}', None
    elif opc == 42:
        b = get_inc_text8()
        return f'mov r{bot(b)}, sizeof(arr<r{top(b)}>)', None
    elif opc == 0xff:
        magic = []
        for i in range(0x13):
            magic.append(get_inc_text8())
        if bytes(magic) == b'PleaseGiveMeTheFlag':
            return f'sysflag [valid]', None
        else:
            return f'sysflag [invalid]' 
    else:
        print(hex(opc))
        exit()
        return f'db 0x{opc:02x}', None

if __name__ == '__main__':
    main()
