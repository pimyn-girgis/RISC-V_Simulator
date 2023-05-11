#include "memory.h"

int main() {
  std::string line = "addi x1, x0, 145";
  std::cout << "line: " << line << std::endl;
  memory mem;
  std::cout << "line: " << line << std::endl;
  mem.set_sectionAddresses(new std::vector<std::pair<const char *, size_t>>(
      {{"text", 0x00000000}, {"data", 0x00400000}, {"stack", 0x00800000}}));
  return 0;
}
