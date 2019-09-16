
MIN_WAIT_TIME = 30
MAX_WAIT_TIME = 120
MIN_WALK_TIME = 60
MAX_WALK_TIME = 240
SCAN_DISTANCE = 120
ATTACK_TIME = 150

main:

.waiting:
; Decide how long to wait here
push MAX_WAIT_TIME
push MIN_WAIT_TIME
call rand_int
mov esi, eax

.wait_loop:
pause

call look_for_player
test eax, eax
jnz .wait_loop

; Stop moving and wait
mov eax, SYS_WALK
xor ebx, ebx
xor ecx, ecx
int 0x80

dec esi
jnz .wait_loop

.wander:
; Pick a random direction
push 4
push 0
call rand_int
; Walk in that direction
mov ebx, [directions + eax * 8]
mov ecx, [directions + eax * 8 + 4]
mov eax, SYS_WALK
int 0x80

; Pick a random amount of time to walk
push MAX_WALK_TIME
push MIN_WALK_TIME
call rand_int
mov esi, eax

.walk_loop:
pause

call look_for_player
test eax, eax
jnz .waiting
dec esi
jnz .walk_loop

jmp .waiting


look_for_player:
push ebx

; Scan area
mov eax, SYS_SCAN_AREA
mov ebx, SCAN_DISTANCE
mov ecx, scan_results
mov edx, end_scan - scan_results
int 0x80

mov ecx, 0
.scan_loop:
cmp ecx, eax
jge .player_not_found
imul edx, ecx, 12
cmp dword [scan_results + edx + 8], SCAN_PLAYER
jne .next

; Found the player, walk there
mov eax, SYS_WALK
mov ebx, [scan_results + edx]
mov ecx, [scan_results + edx + 4]
int 0x80

.check_for_fire:
; Check for firing
cmp dword [time_until_attack], 0
je .attack

dec dword [time_until_attack]
mov eax, 1
jmp .done

.attack:
mov eax, SYS_ATTACK
int 0x80
mov dword [time_until_attack], ATTACK_TIME
mov eax, 1
jmp .done

.next:
inc ecx
jmp .scan_loop

.player_not_found:
xor eax, eax

.done:
pop ebx
ret


rand_int:
.min = 4
.max = 8
mov ecx, [esp + .max]
sub ecx, [esp + .min]
mov eax, SYS_RAND
int 0x80
xor edx, edx
div ecx
add edx, [esp + .min]
xchg eax, edx
ret 8


directions:
dd 1, 0
dd -1, 0
dd 0, 1
dd 0, -1


.data
id:
dd 0

scan_results:
dd 0, 0, 0
dd 0, 0, 0
dd 0, 0, 0
dd 0, 0, 0
dd 0, 0, 0
dd 0, 0, 0
dd 0, 0, 0
dd 0, 0, 0
end_scan:

time_until_attack:
dd 0

