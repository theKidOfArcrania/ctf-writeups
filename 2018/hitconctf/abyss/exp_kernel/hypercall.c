#include "hypercall.h"
#include "mm.h"

int hp_read(int fd, char *buff, uint32_t len) {
  return serial_comm_args(HP_READ, fd, physical(buff), len);
}

int hp_write(int fd, char *buff, uint32_t len) {
  return serial_comm_args(HP_WRITE, fd, physical(buff), len);
}

int hp_open(char *name) {
  return serial_comm(HP_OPEN, physical(name));
}

int hp_close(int fd) {
  return serial_comm(HP_CLOSE, fd);
}

int hp_lseek(int fd, off_t offset, int whence) {
  return serial_comm_args(HP_LSEEK, fd, offset, whence);
}

void hp_exit(int num) {
  serial_comm(HP_EXIT, num);
  __builtin_unreachable();
}

int hp_ioctl(int fd, uint64_t request, void *mem) {
  return serial_comm_args(HP_IOCTL, fd, request, physical(mem));
}


void __attribute__((noreturn)) hlt();
void hp_panic(const char *s) {
  serial_comm(HP_PANIC, ((uint64_t)s & ~KERNEL_BASE_OFFSET));
  hlt();
}
