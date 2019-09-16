extern getchar
extern putchar
global main

section .text
main:
	push ebp
  mov ebp, esp
	sub esp, 32
	
	lea eax, [ebp - 32]
	push eax
	push eax
	call input
	
	mov eax, 0

  leave
	ret

strcpy:
	push ebp
	push esi
	push edi
	mov ecx, [__cookie]
	xor ecx, [esp + 12]
	push ecx
	mov ebp, esp

	mov edi, [ebp + 20]
	mov esi, [ebp + 24]
.copy:
	mov al, [esi]
	mov [edi], al
	test al, al
	jz .end
	inc esi
	inc edi
	jmp .copy
.end:

	pop ecx
	xor ecx, [esp + 12]
	cmp ecx, [__cookie]
	jne __stack_chk_fail
	pop edi
	pop esi
	pop ebp
	ret 8



input:
        push ebp
        push esi
        mov ecx, [__cookie]
        xor ecx, [esp + 8]
        push ecx
        mov ebp, esp
        sub esp, 36

        mov dword [ebp - 36], 0
        xor ecx, ecx 
.clear_loop: 
        mov byte [ebp - 32 + ecx], 0 
        inc ecx 
        cmp ecx, 32 
        jb .clear_loop 
 
.input_loop: 
	call getchar
        cmp al, 0xa 
        je .end_input 
        cmp al, 8 
        ;je .backspace 
 
        mov ecx, [ebp - 36] 
        mov [ebp - 32 + ecx], al 
        inc dword [ebp - 36] 
        jmp .input_loop 
 
.backspace: 
        cmp dword [ebp - 36], 0 
        je .input_loop 
        mov al, 8 
        mov al, ' ' 
        mov al, 8 
        dec dword [ebp - 36] 
        jmp .input_loop 
 
.end_input: 
 
        mov ecx, [ebp - 36] 
        mov byte [ebp - 32 + ecx], 0 
 
        lea eax, [ebp - 32] 
	      push eax 
        push dword [ebp + 16] 
        call strcpy
 
        mov esp, ebp 
        pop ecx 
        xor ecx, [esp + 8] 
        cmp ecx, [__cookie] 
        jne __stack_chk_fail 
        pop esi 
        pop ebp
        ret 4

__stack_chk_fail:
	int3

section .data
__seed:
  dd 0
__cookie:
  dd 0x15679305
