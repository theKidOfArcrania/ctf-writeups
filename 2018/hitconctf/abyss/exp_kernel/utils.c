#include "hypercall.h"
#include "utils.h"
#include "string.h"
#include "mm.h"

// This is a POOR algorithm for reading one line, please do not use.
int _getline(int fd, char *buff, size_t size) {
  int nbytes = 0;
  while (nbytes < size - 1) {
    if (hp_read(fd, buff, 1) < 1) {
      if (nbytes == 0)
        return -1;
      else
        break;
    }
    if (*buff == '\n') {
      *buff = 0;
      return nbytes;
    }

    nbytes++;
    buff++;
  }

  *buff = 0;
  return nbytes;
}

static char nl = '\n';
void _puts(const char *buff) {
  hp_write(1, (char*)buff, strlen(buff));
  hp_write(1, &nl, 1);
}

static const char hexvals[] = "0123456789abcdef";
static char hex_buff[17];
void writeHex(uint64_t val) {
  int dig = 16;
  while (dig --> 0) {
    hex_buff[15 - dig] = hexvals[(val >> (dig * 4)) & 0xf];
  }
  hex_buff[16] = '\n';
  hp_write(1, hex_buff, 17);
}
