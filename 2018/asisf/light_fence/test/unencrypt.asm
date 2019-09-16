BITS 64

%define REL_LOC 0x1CB0
%define REL_HUFF 0x18a0
%define REL_NSG 0x14a0

%macro xcall 1
  db 0xe8
  dd %1 - (REL_LOC + $ - $$ + 4)
%endmacro


unencrypt: ; file
  push rbx
  push rbp
  mov rbp, rsp
  sub rsp, 0x1510

  mov rbx, rdi

  mov rsi, 0
  mov eax, 2 ; open
  syscall
  mov [rbp - 0x1504], eax

  mov edi, eax
  lea rsi, [rbp - 0x100]
  mov edx, 0x4
  mov eax, 0 ; read
  syscall

  mov al, [rbp - 0x100 + 3]
  mov [rbp - 0x150d], al

  mov edx, 0x100
  mov eax, 0 ; read
  syscall

  ; Create huff extension filename
  mov rdx, 0x400
  mov rsi, rbx
  lea rdi, [rbp - 0x500]
  call strncpy

  mov rdx, 0x400
  lea rsi, [rel huff_file]
  lea rdi, [rbp - 0x500]
  call strcat

  ; Copy contents of our encoded file into huff file.
  mov edx, 436 ; 0664
  mov esi, 65 ; O_WRONLY | O_CREAT
  lea rdi, [rbp - 0x500]
  mov eax, 2 ; open
  syscall
  mov [rbp - 0x1508], eax

.copy_loop:
  mov edx, 0x1000
  lea rsi, [rbp - 0x1500]
  mov edi, [rbp - 0x1504]
  mov eax, 0 ; read
  syscall

  cmp eax, 0
  jle .end_loop

  mov edx, eax
  lea rsi, [rbp - 0x1500]
  mov edi, [rbp - 0x1508]
  mov eax, 1 ; write
  syscall
  jmp .copy_loop

.end_loop:
  mov rdx, 0x400
  mov rsi, rbx
  lea rax, [rbp - 0x900]
  mov rdi, rax
  call strncpy

  mov rdx, 0x400
  lea rsi, [rel nsg_file]
  lea rdi, [rbp - 0x900]
  call strcat

  ; Remove extension for output file
  mov rdx, 0x400
  mov rsi, rbx
  lea rdi, [rbp - 0xd00]
  call strncpy

  lea rdi, [rbp - 0xd00]
  call strlen
  mov byte [(rbp - 0xd00) + rax - 4], 0

  ; Call huff decryption
  xor ecx, ecx
  mov cl, [rbp - 0x150d] ; number of bits to skip
  lea rdx, [rbp - 0x100] ; bit lengths
  lea rsi, [rbp - 0x900] ; nsg file
  lea rdi, [rbp - 0x500] ; huff file
  xcall REL_HUFF ; 0x555555555ddd

  lea rsi, [rbp - 0xd00] ; output_file
  lea rdi, [rbp - 0x900] ; nsg file
  xcall REL_NSG
  
  lea rdi, [rbp - 0x900] ; nsg file
  mov eax, 87 ; unlink
  syscall

  lea rdi, [rbp - 0x500] ; huff file
  mov eax, 87 ; unlink
  syscall

  leave
  pop rbx
  ret

strlen: ; (str)
  push rbp
  mov rbp, rsp
  xor ecx, ecx
  xor al, al
  not ecx
  cld
  repne scasb
  not ecx
  lea eax, [ecx - 1]
  leave
  ret

strcat: ; (dst, str, len)
  push rbp
  mov rbp, rsp
  xor eax, eax
  mov ecx, edx
  cld
  repne scasb 
  jnz .exit

  dec rdi
  mov edx, ecx
  call strncpy
.exit:
  leave
  ret
  

strncpy: ; (dst, src, len)
  push rbp
  mov rbp, rsp
  mov ecx, edx
  test ecx, ecx
  jz .end
.loop:
  mov al, [rsi]
  mov [rdi], al
  test al, al
  jz .end
  
  inc rdi
  inc rsi
  dec ecx
  jnz .loop
.end:
  leave
  ret

huff_file:
  db ".huff", 0

nsg_file:
  db ".nsg", 0

times (0x20e - ($ - $$)) db 0
