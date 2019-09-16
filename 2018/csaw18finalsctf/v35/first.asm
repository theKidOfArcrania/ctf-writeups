mov ecx, exp_len - exp
mov esi, exp
mov dx, 0
rep outsb
hlt

exp:
  db "12345678901234567890123456789012345678901234", 0xa7, 0x10, 0x00, 0x00, '\n'
exp_len:
