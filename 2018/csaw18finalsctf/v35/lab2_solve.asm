%include "nasmx.inc"

IMPORT puts
ENTRY main_proc

section .data
start_data:
  db "DSFF"
  times 13 db 0

section .text
PROC main_proc
LOCALS NONE

  lea rsi, [rel start_data]
  lea rbx, [rel start_data + 4]

  mov edx, 0xfa

  mov al, [rsi]
  rol edx, 5
  xor dl, al
  add dl, 0xab
  ; edx = (0x1f40 ^ msg[0]) + 0xab

  mov al, [rsi+1]
  rol edx, 3 
  xor dl, al
  add dl, 0x45

  mov al, [rsi+2]
  rol edx, 1
  xor dl, al
  add dl, 0x12

  mov al, [esi+3]
  rol edx, 9
  xor dl, al
  add dl, 0xcd

  mov cl, dl
  and cl, 15
  add cl, 'a'

  mov [rbx], cl
  inc rbx

  rol edx, 12
  xor dl, cl
  add dl, 0x87

  mov cl, dl
  and cl, 15
  add cl, 'a'
  mov [rbx], cl
  inc rbx

  rol edx, 3
  xor dl, cl
  add dl, 0xef

  mov cl, dl
  and cl, 15
  add cl, 'C'
  mov [rbx], cl
  inc rbx
  
  rol edx, 1
  xor dl, cl
  add dl, 0x10

  mov cl, dl
  and cl, 15
  add cl, 'f'
  mov [rbx], cl
  inc rbx
  
  rol edx, 13
  xor dl, cl
  add dl, 0x9a

  mov cl, dl
  and cl, 15
  add cl, 'e'
  mov [rbx], cl
  inc rbx
  
  rol edx, 9
  xor dl, cl
  add dl, 0xa8

  mov cl, dl
  and cl, 15
  add cl, 'D'
  mov [rbx], cl
  inc rbx

  rol edx, 7
  xor dl, cl
  add dl, 0xca

  mov cl, dl
  and cl, 15
  add cl, 'D'
  mov [rbx], cl
  inc rbx

  rol edx, 2
  xor dl, cl
  add dl, 0x91

  mov cl, dl
  and cl, 15
  add cl, 'c'
  mov [rbx], cl
  inc rbx
  
  rol edx, 5
  xor dl, cl
  add dl, 0x86

  mov cl, dl
  and cl, 15
  add cl, 'A'
  mov [rbx], cl
  inc rbx
  
  rol edx, 6
  xor dl, cl
  add dl, 0xf1

  mov cl, dl
  and cl, 15
  add cl, 'e'
  mov [rbx], cl
  inc rbx
  
  rol edx, 3
  xor dl, cl
  add dl, 0x1f

  mov cl, dl
  and cl, 15
  add cl, 'B'
  mov [rbx], cl
  inc rbx

  rol edx, 4
  xor dl, cl
  add dl, 0x90

  mov cl, dl
  and cl, 15
  add cl, 'f'
  mov [rbx], cl
  inc rbx

  INVOKE puts, start_data

ENDPROC
