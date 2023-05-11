#include "riscv.h"

int main() {
  riscv program;
  fs::path path = "/Users/bemen/Documents/AUC/22_23/Spring/CSCE 2303/RISC-V_Simulator/bin/text.txt";
  program.read_program(path);
  std::cout << std::endl;
  while(!program.end_of_program()) {
    program.execute();
  }
  return 0;
}
