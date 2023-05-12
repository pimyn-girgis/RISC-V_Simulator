#define _CRT_SECURE_NO_WARNINGS
#include "riscv.h"
namespace fs = std::filesystem;

int main() {
  riscv program;
  fs::path path = "./program.txt";
  program.read_program(path);
  std::cout << std::endl;
  while (!program.end_of_program()) {
    program.execute();
  }
  return 0;
}
