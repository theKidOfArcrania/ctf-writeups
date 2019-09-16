#include <stdio.h>
#include <stdint.h>
#include <vector>

void print_vector(std::vector<int>& f) {
  uint64_t* dta = (uint64_t*)&f;

#define size(ind) ((dta[(ind)] - dta[0]) / sizeof(int))
  printf("Vector: %016lx (len = %ld, cap = %ld)\n", dta[0], size(1), size(2));
}

int main() {
  std::vector<int> f;

  for (int i = 0; i < 32; i++) {
    print_vector(f);
    f.push_back(i);
  }
}
