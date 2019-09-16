#define _GNU_SOURCE

#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>

#include <linux/seccomp.h>
#include <linux/filter.h>
#include <linux/audit.h>
#include <linux/signal.h>
#include <sys/ptrace.h>
#include <sys/mman.h>
#include <sys/prctl.h>

#define BLK(a, b, c, d) ((struct sock_filter) {a, b, c, d})

struct sock_filter prog[8] = {
  BLK(0x20, 0, 0, 4),  // LD arch
  BLK(0x15, 0, 5, 0xC000003E),
  BLK(0x20, 0, 0, 0),  // LD nr
  BLK(0x35, 3, 0, 0x40000000), //
  BLK(0x15, 1, 0, 0x5F),
  BLK(6, 0, 0, 0x7FFF0000), //okay
  BLK(6, 0, 0, 0x50001), // errno with 1
  BLK(6, 0, 0, 0)}; // kill


int main(int argc, char** argv, char** envp) {
  struct sock_fprog pr = {8, prog};

  prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
  syscall(SYS_seccomp, SECCOMP_SET_MODE_FILTER, 0, &pr);
  umask(0);
  execve(argv[1], argv + 2, 0);
}
