BITS 64


%define marker 0x1583
%define honco 0x1508

mov rax, marker
mov edi, 0x64
out dx, al

; dump honco
mov rax, honco
mov edi, 0x66
out dx, al

mov rax, marker
mov edi, 0x64
out dx, al

; Exit
mov edx, 0xc
int 0x80
hlt
