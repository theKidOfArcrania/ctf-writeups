#include <stdint.h>

struct string {
  char *ptr;
  uint64_t size;
  char pad[0x10];
};

struct string x;
