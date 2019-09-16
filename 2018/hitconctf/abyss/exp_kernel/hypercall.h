#ifndef _HYPERCALL_H
#define _HYPERCALL_H

#include "mm.h"

#include <inttypes.h>
#include <sys/types.h>


#define HP_OPEN    0x8000
#define HP_READ    0x8001
#define HP_WRITE   0x8002
#define HP_LSEEK   0x8003
#define HP_CLOSE   0x8004
#define HP_FSTAT   0x8005
#define HP_EXIT    0x8006
#define HP_ACCESS  0x8007
#define HP_IOCTL   0x8008
#define HP_PANIC   0xFFFF



// Serial communication for hypercalls
static inline int serial_comm(uint16_t port, uint32_t data) {
  int ret = 0;
  asm volatile(
    "mov dx, %[port];"
    "mov eax, %[data];"
    "out dx, eax;"
    "in eax, dx;"
    "mov %[ret], eax;"
    : [ret] "=r"(ret)
    : [port] "r"(port), [data] "r"(data)
    : "rax", "rdx"
    );
  return ret;
}
static inline int serial_comm_args(uint16_t port, uint64_t arg1, uint64_t arg2, 
    uint64_t arg3) {
  uint64_t *kbuf = kmalloc(sizeof(uint64_t) * 3, 0);
  kbuf[0] = arg1;
  kbuf[1] = arg2;
  kbuf[2] = arg3;
  int ret = serial_comm(port, physical(kbuf));
  kfree(kbuf);

  return ret;
}

int hp_read(int fd, char *buff, uint32_t len);
int hp_write(int fd, char *buff, uint32_t len);
int hp_open(char *name);
int hp_close(int fd);
int hp_lseek(int fd, off_t offfset, int whence);
void __attribute__((noreturn)) hp_exit(int num);
int hp_ioctl(int fd, uint64_t request, void *mem);
void __attribute__((noreturn)) hp_panic();

#define panic hp_panic

#endif
