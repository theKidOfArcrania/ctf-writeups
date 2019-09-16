.loop:
  ipause
  mov ebp, esp
  sub esp, 0x60
  mov eax, SYS_SCAN_AREA
  xor ebx, ebx
  dec bl
  mov ecx, esp
  xor edx, edx
  mov dl, 0x60
  int 0x80

  lea edi, [ebp - 0x60]
  xor ebx, ebx
  mov bl, SCAN_PLAYER

  xor ecx, ecx
.scan_loop:
  cmp ecx, eax
  jge .loop_fail

  imul edx, ecx, 12
  cmp dword [edi + edx + 8], ebx
  jne .scan_loop

  xor eax, eax
  mov al, SYS_WALK
  mov ebx, [edi + edx]
  mov ecx, [edi + edx + 4]
  int 0x80
  jmp .loop

.loop_fail:
  xor eax, eax
  mov al, SYS_WALK
  xor ebx, ebx
  xor ecx, ecx
  int 0x80
  jmp .loop
