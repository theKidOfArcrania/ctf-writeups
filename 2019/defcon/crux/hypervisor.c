#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd = open("crux.patched", 0);

  off_t size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);

  void (*ret)() = mmap(0, 0x6000, 7, MAP_ANONYMOUS | MAP_PRIVATE | MAP_FIXED, -1, 0);
  read(fd, (void*)ret, size);

//  asm volatile ("int3");
  ret();
}
