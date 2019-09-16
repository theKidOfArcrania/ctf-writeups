#include <stdint.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct string {
  char *s;
  uint64_t size;
  char pad[0x10];
};

struct string* str_cstr(char *a){
  struct string *ret = malloc(sizeof(*ret));
  ret->s = a;
  ret->size = strlen(a);
}

int main(int argc, char** argv) {
  void **exe = dlopen("./gibberish_check", RTLD_NOW);
  if (argc != 3) {
    printf("%s STR_A STR_B\n", argv[0]);
    return 0;
  }

  int ret = ((int (*)(struct string*, struct string*))((*exe) + 0x164A))(
      str_cstr(argv[1]), str_cstr(argv[2]));

  printf("%d\n",ret );
}
