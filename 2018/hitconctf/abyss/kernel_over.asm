BITS 64

kmalloc: equ 0x15e0

kern:
  jmp kern2

prompt: db "Kernel code please: "
prompt_len: equ $ - prompt
kern_code: dq 0xffffffffffffffff

KERN_LEN: equ 0x2000

serial_comm:
  mov dx, di
  mov eax, esi
  out dx, eax
  in eax, dx

  cmp eax, 0
  mov edi, eax

  ret


times (0x67 - ($-$$)) db 0
db 0x15 ; This has to be at least 21?

kern2:
  mov qword [rel arg1], 1
  mov qword [rel arg2], prompt - $$
  mov qword [rel arg3], prompt_len
  mov di, 0x8002 ; write
  mov esi, arg1 - $$
  call serial_comm

  mov edi, KERN_LEN
  mov esi, 0x1000
  call $$ + kmalloc
  mov qword [rel kern_code], rax

  mov rdx, 0x8000000000
  xor rax, rdx

  mov qword [rel arg1], 0
  mov qword [rel arg2], rax
  mov qword [rel arg3], KERN_LEN
  mov di, 0x8001 ; read
  mov esi, arg1 - $$
  call serial_comm

  mov rax, [rel kern_code]
  jmp rax
  ;mov qword [prompt], rax

  ;jmp kern2
  hlt

hlt:
  hlt
  ret
  
arr:  dq 0

times (0x14D - ($-$$)) db 0x00
kernel_rsp: dq 0x8000100100     ; kernel_rsp
dq 0xcccccccccccccc ; user_rsp
jmp kern

times (0x17f - ($-$$)) db 0xcc
jmp kern

arg1: dq 0
arg2: dq 0
arg3: dq 0
