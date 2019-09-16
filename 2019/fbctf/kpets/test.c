#include <stdio.h>
#include <fcntl.h>

int main() {
  int fd = open("/dev/kpets", O_RDONLY);
  char buff[0x100];

  read(fd, buff, 41);
  puts(buff);
}

