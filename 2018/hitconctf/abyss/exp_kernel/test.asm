sigframe:
  dq 0xfffffffffffffffb ; uc_flags: don't set 0x4
  dq 0xffffffffffffffff ; &uc
  dq 0xFFFFFFFFFFFFFFFF ; uc_stack.sp_sp
  dq 0 ; uc_stack.ss_flags
  dq 0 ; uc_stack.ss_size
  dq 1 ; r8
  dq 2 ; r9
  dq 3 ; r10
  dq 4 ; r11
  dq 5 ; r12
  dq 6 ; r13
  dq 7 ; r14
  dq 8 ; r15
  dq 9 ; rdi
  dq 0xa ; rsi
  dq 0xb ; rbp
  dq 0xc ; rbx
  dq 0xd ; rdx
  dq 0xe ; rax
  dq 0xf ; rcx
  dq 0x10 ; rsp
  dq hello ; rip
  dq 0x0 ; flags
  dq 0x33 ; cs, ds, fs
  dq 0 ; err
  dq 0 ;
  dq 0 ; 
  dq 0 ; 
  dq 0 ; 
  dq 0 ; 
  dq 0 ; 

global _start
_start:
  lea rsp, [rel sigframe]
  mov eax, 0xf
  syscall

hello:
  mov eax, 60
  syscall
