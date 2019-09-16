4000: sub sp, 0xf0
4002: sub sp, 0xf0
4004: sub sp, 0xf0
4006: sub sp, 0x30
4008: mov r15, 0x00000001
400e: mov r0, 0x00004800
4014: mov r1, 0x0000003c
401a: syswrite [r0], len=r1
401c: mov r0, 0x00000000
4022: mov r1, 0x00000004
4028: sysread [r0], len=r1
402a: mov r0, 0x00000000
4030: mov r3, byte [r0]
4032: mov r9, 0x00000031
4038: sub r9, r3
403a: bz r9, off_4058
403e: mov r9, 0x00000032
4044: sub r9, r3
4046: bz r9, off_40d1
404a: mov r9, 0x00000033
4050: sub r9, r3
4052: bz r9, off_4130
4056: sysexit 0
4058: mov r0, 0x0000483c
405e: mov r1, 0x0000001a
4064: syswrite [r0], len=r1
4066: sub sp, 0x40
4068: mov r0, 0x00000000
406e: mov r1, 0x00000080
4074: sysread [sp + r0], len=r1
4076: mov r5, r0
4078: alloc_byte r0
407a: mov r6, r0
407c: mov r4, 0x00000000
4082: mov r7, r4
4084: sub r7, r5
4086: bz r7, off_4094
408a: mov r1, byte [sp + r4]
408c: mov byte arr<r6>[r4], r1
408f: add r4, r15
4091: jmp off_4082
4094: mov r1, 0x00000002
409a: alloc_dword r1
409c: mov r1, 0x00000000
40a2: mov dword arr<r0>[r1], r6
40a5: mov r1, 0x00000004
40ab: mov r2, dword [r1]
40ad: mov r1, 0x00000001
40b3: mov dword arr<r0>[r1], r2
40b6: mov r1, 0x00000004
40bc: mov dword [r1], r0
40be: add sp, 0x40
40c0: mov r0, 0x00004856
40c6: mov r1, 0x00000016
40cc: syswrite [r0], len=r1
40ce: jmp off_400e
40d1: mov r1, 0x00000004
40d7: mov r0, dword [r1]
40d9: call off_40df
40dc: jmp off_400e
40df: bnz r0, off_40e4
40e3: ret
40e4: sub sp, 0x40
40e6: mov r9, r0
40e8: mov r1, 0x00000000
40ee: mov r0, dword arr<r9>[r1]
40f1: mov r3, sizeof(arr<r0>)
40f3: mov r4, 0x00000000
40f9: mov r7, r3
40fb: sub r7, r4
40fd: bz r7, off_410b
4101: mov r1, byte arr<r0>[r4]
4104: mov byte [sp + r4], r1
4106: add r4, r15
4108: jmp off_40f9
410b: mov r2, 0x00000000
4111: syswrite [sp + r2], len=r3
4113: mov r0, 0x0000489c
4119: mov r1, 0x00000001
411f: syswrite [r0], len=r1
4121: mov r1, 0x00000001
4127: mov r0, dword arr<r9>[r1]
412a: call off_40df
412d: add sp, 0x40
412f: ret
4130: mov r0, 0x00000004
4136: mov r1, dword [r0]
4138: bz r1, off_416b
413c: mov r0, 0x00000000
4142: mov r2, dword arr<r1>[r0]
4145: mov r0, 0x00000001
414b: mov r3, dword arr<r1>[r0]
414e: free r2
4150: free r1
4152: mov r0, 0x00000004
4158: mov dword [r0], r3
415a: mov r0, 0x0000486c
4160: mov r1, 0x00000015
4166: syswrite [r0], len=r1
4168: jmp off_400e
416b: mov r0, 0x00004881
4171: mov r1, 0x0000001b
4177: syswrite [r0], len=r1
4179: jmp off_400e
417c: nop
417d: nop
417e: nop
417f: nop
