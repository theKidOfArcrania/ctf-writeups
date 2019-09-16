#include <stdint.h>
#include <unistd.h>

enum OP {
    INSN_DST = 0xDD,
    INSN_HLT = 0xFE,
    INSN_MOV  = 0x88,
    INSN_MOVI = 0x89,
    INSN_PUSH = 0xED,
    INSN_POP = 0xB1,
    INSN_ADD = 0xD3,
    INSN_ADDI = 0xC6,
    INSN_SUB = 0xD8,
    INSN_SUBI = 0xEF,
    INSN_MUL = 0x34,
    INSN_DIV = 0xB9,
    INSN_XOR = 0xB7,
    INSN_CMP = 0xCC,
    INSN_JMP = 0x96,
    INSN_JE = 0x81,
    INSN_JNE = 0x9E,
    INSN_JG = 0x2F,
    INSN_JGE = 0xF4,
    INSN_JL = 0x69,
    INSN_JLE = 0x5F,
    INSN_LDF = 0xD9,
    INSN_AGE = 0x9B,
    INSN_AGD = 0x7F,
    INSN_LEAK = 0x42
};

// Register opcodes
enum REG {
    KAX = 0x0A,
    KBX,
    KCX,
    KDX,
    KPC,
    KRX,
    KSP,
    KFLAGS
};

// Flag bits
enum KFLAGS { ZF, SF };

#define BEGIN_VM int main() { \
  char arr[0x1000], *ptr = arr;

#define END_VM write(1, arr, ptr - arr); }

#define _W1(v) do {*ptr = (char)(v); ptr++;} while(0)
#define _W2(v) do {*(uint16_t*)ptr = (uint16_t)(v); ptr+=2;} while(0)
#define _W4(v) do {*(uint32_t*)ptr = (uint32_t)(v); ptr+=4;} while(0)
#define _W8(v) do {*(uint64_t*)ptr = (uint64_t)(v); ptr+=8;} while(0)


#define POP(reg) {_W1(INSN_POP); _W1(reg); }
#define PUSH(reg) {_W1(INSN_PUSH); _W1(reg); }
#define ADD(dst, src) {_W1(INSN_ADD); _W1(dst); _W1(src); }
#define SUB(dst, src) {_W1(INSN_SUB); _W1(dst); _W1(src); }
#define MOV(dst, src) {_W1(INSN_MOV); _W1(dst); _W1(src); }
#define ADDI(dst, imm) {_W1(INSN_ADDI); _W1(dst); _W8(imm); }
#define SUBI(dst, imm) {_W1(INSN_SUBI); _W1(dst); _W8(imm); }
#define MOVI(dst, imm) {_W1(INSN_MOVI); _W1(dst); _W8(imm); }

#define LDF() {_W1(INSN_LDF); }
#define DST() {_W1(INSN_DST); }
#define AGE(reg) {_W1(INSN_AGE); _W1(reg); }
#define AGD() {_W1(INSN_AGD); }
#define LEAK() {_W1(INSN_LEAK); _W1(0x3f); }

