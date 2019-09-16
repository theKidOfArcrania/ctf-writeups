#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  void *a, *b, *c;
  a = mmap(0LL, 0x6000uLL, 3, 34, -1, 0LL);
  b = mmap(0LL, 0x2000uLL, 3, 34, -1, 0LL);
  c = mmap(0LL, 0x1000uLL, 3, 34, -1, 0LL);

  printf("%p %p %p\n", a, b, c);

  FILE* f = fopen("/proc/self/maps", "r");
  char buff[0x1000];
    
  int len = fread(buff, 1, sizeof(buff), f);
  fwrite(buff, len, 1, stdout);
  
}
