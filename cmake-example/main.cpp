#include "Vtop.h"
#include "rubbler.h"
#include "verilated.h"
#include <cstdint>
#include <cstdio>
#include <memory>

#define MAX_SIZE 1024

using namespace std;

void bytes_to_pattern_file(uint8_t *bytes, size_t size, const char *file_name);

int main(int argc, char *argv[]) {
  unique_ptr<VerilatedContext> context(new VerilatedContext());
  unique_ptr<Vtop> top(new Vtop(context.get(), "TOP"));
  const svScope scope = svGetScopeFromName("TOP.top");
  assert(scope);
  svSetScope(scope);

  auto source = "add t0, t1, t2";
  auto bytes = (uint8_t *)malloc(sizeof(uint8_t) * MAX_SIZE);
  uintptr_t size = MAX_SIZE;
  assert(rubble(source, bytes, &size));

  bytes_to_pattern_file(bytes, size, "hex_pattern.txt");

  top->write_mem("hex_pattern.txt");

  assert(top->read_mem(0, 1) == bytes[0]);
  assert(top->read_mem(1, 1) == bytes[1]);
  assert(top->read_mem(2, 1) == bytes[2]);
  assert(top->read_mem(3, 1) == bytes[3]);

  return 0;
}

void bytes_to_pattern_file(uint8_t *bytes, size_t size, const char *file_name) {
  auto f = fopen(file_name, "w");
  for (int i = 0; i < size; i++) {
    fprintf(f, "%02x\n", bytes[i]);
  }
  fclose(f);
}
