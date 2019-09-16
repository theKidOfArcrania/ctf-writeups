#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <string>

void print_string(std::string &s) {
  for (int i = 0; i < sizeof(s); i++) {
    printf("%02hhx ", ((char*)&s)[i]);
    if ((i + 1) % 16 == 0)
      puts("");
  }
}

void print_vector(std::vector<int>& f) {
  uint64_t* dta = (uint64_t*)&f;

#define size(ind) ((dta[(ind)] - dta[0]) / sizeof(int))
  printf("Vector: %016lx (len = %ld, cap = %ld)\n", dta[0], size(1), size(2));
}

int main() {
  std::string s("sdafsda");
  print_string(s);
}
