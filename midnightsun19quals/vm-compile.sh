#!/bin/bash

set -e

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 FILE"
  exit 1
fi


cat > tmptmp.c <<EOF
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct inst {
  uint16_t opcode:5;
  uint16_t r_dst:4;
  uint16_t r_src:4;
  uint16_t is_imm:1;
  uint16_t pad:2;
  uint16_t imm:16;
};


#define INST_RI(opcode, r_dst, imm) ((struct inst) {opcode, (r_dst), 0, 1, 0, (imm)}),
#define INST_RR(opcode, r_dst, r_src) ((struct inst) {opcode, (r_dst), (r_src), 0, 0, 0}),
#define INST_N(opcode) ((struct inst) {opcode, 0, 0, 0, 0, 0}),

enum syscalls {
  SYS_LS, SYS_WRITE, SYS_UID, SYS_FLAG, SYS_RANDOM
};

enum opcodes {
  O_MOV, O_ADD, O_SUB, O_XCHG, O_XOR, O_PUSH, O_POP, O_SSET, O_SGET, O_SYSCALL, O_DEBUG
};

enum registers {
  R_SYS = 1, R_A1 = 2, R_A2 = 3, R_SP = 14, R_PC = 15
};

#define MOV(r_dst, r_src) INST_RR(O_MOV, r_dst, r_src)
#define MOVI(r_dst, imm) INST_RI(O_MOV, r_dst, imm)
#define ADD(r_dst, r_src) INST_RR(O_ADD, r_dst, r_src)
#define ADDI(r_dst, imm) INST_RI(O_ADD, r_dst, imm)
#define SUB(r_dst, r_src) INST_RR(O_SUB, r_dst, r_src)
#define SUBI(r_dst, imm) INST_RI(O_SUB, r_dst, imm)
#define XCHG(r_dst, r_src) INST_RR(O_XCHG, r_dst, r_src)
#define XCHGI(r_dst, imm) INST_RI(O_XCHG, r_dst, imm)
#define XOR(r_dst, r_src) INST_RR(O_XOR, r_dst, r_src)
#define XORI(r_dst, imm) INST_RI(O_XOR, r_dst, imm)
#define PUSH(r_dst) INST_RR(O_PUSH, r_dst, 0)
#define PUSHI(imm) INST_RI(O_PUSH, 0, imm)
#define POP(r_dst) INST_RR(O_POP, r_dst, 0)
#define SGET(r_dst, r_ind) INST_RR(O_SGET, r_dst, r_ind)
#define SSET(r_ind, r_src) INST_RR(O_SSET, r_ind, r_src)
#define SSETI(r_ind, imm) INST_RI(O_SSET, r_ind, imm)
#define DEBUG() INST_N(O_DEBUG)
#define SYSCALL() INST_N(O_SYSCALL)

#define BEGIN_VM int main() { struct inst insts[] = {
#define END_VM INST_N(0)}; fwrite(insts, 1, sizeof(insts) - sizeof(struct inst), stdout); }

EOF

cat "$1" >> tmptmp.c

gcc tmptmp.c -o tmptmp
./tmptmp
rm tmptmp.c tmptmp
