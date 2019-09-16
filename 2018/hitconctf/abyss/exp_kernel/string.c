#include "string.h"

/* no memory accessibility checks in these string functions */

uint64_t strlen(const char *s) {
  return strnlen(s, ~0ll);
}

uint64_t strnlen(const char *s, uint64_t maxlen) {
  uint64_t i = 0;
  while(i < maxlen) {
    if(*s == 0) return i;
    i++; s++;
  }
  return maxlen;
}

void *memset(void *b, int c, uint64_t len) {
  for(int i=0;i<len;i++)
    ((uint8_t*)b)[i] = (uint8_t)c;
  return b;
}

void *memcpy(void *dst, const void *src, uint64_t n) {
  asm(
    "mov rcx, %[n];"
    "rep movsb byte ptr [%[dst]], byte ptr [%[src]];"
    :: [n]"r"(n), [dst]"D"(dst), [src]"S"(src) : "rcx"
    );
  return dst;
}

int memcmp(const void *s1, const void *s2, uint64_t n) {
  unsigned char u1, u2;
  for(; n--; s1++, s2++) {
    u1 = *(unsigned char *) s1;
    u2 = *(unsigned char *) s2;
    if (u1 != u2) return u1 - u2;
  }
  return 0;
}

static int hex(char c) {
  if ('a' <= c && c <= 'f')
    return c - 'a' + 10;
  else if ('A' <= c && c <= 'F')
    return c - 'A' + 10;
  else if ('0' <= c && c <= '9')
    return c - '0';
  else
    return -1;
}

uint64_t parseHex(const char *s) {
  uint64_t ret = 0;
  for (int i = 0; i < 16; i++) {
    int h = hex(s[i]);
    if (h == -1)
      break;

    ret <<= 4;
    ret += h;
  }

  return ret;
}
