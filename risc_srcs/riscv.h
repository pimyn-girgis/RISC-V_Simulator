#include "genUtils.h"
#include "memory.h"
#include <array>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class riscv {
private:
  memory mem;
  memory reg;
  size_t pc;
  std::unordered_map<std::string, int> instruction_set;
  std::vector<std::string> instructions;
  std::unordered_map<std::string, int> registers_map;
  std::unordered_map<std::string, int>
      labels; // word addressable relative to start of the program
  void read_line(const std::string
                     &line); // adds an instruction to the instructions vector
  void parse_program(); // parses the instructions vector and adds the machine
                        // code to it
  int parse_operands(int machine, char *operands[3],
                     int inst_num); // returns the machine code for the operands

  // instruction getters
  int get_rd(int instruction);
  int get_rs1(int instruction);
  int get_rs2(int instruction);
  int get_imm(int instruction);
  int get_sep_imm(int instruction);
  int get_upp_imm(int instruction);
  int get_shamt(int instruction);
  int get_opcode(int instruction);
  int get_funct3(int instruction);
  int get_funct7(int instruction);

  // instruction setters
  int set_rd(int instruction, int value);
  int set_rs1(int instruction, int value);
  int set_rs2(int instruction, int value);
  int set_imm(int instruction, int value);
  int set_sep_imm(int instruction, int value);
  int set_upp_imm(int instruction, int value);
  int set_shamt(int instruction, int value);
  int set_opcode(int instruction, int value);
  int set_funct3(int instruction, int value);
  int set_funct7(int instruction, int value);

  void rtype(int instruction);
  void itype(int instruction);
  void stype(int instruction);
  void btype(int instruction);
  void utype(int instruction);
  void jtype(int instruction);
  

  void branch(int instruction);
  void load(int instruction);
  void imm(int instruction);
  void init_reg(fs::path *reg_init_file, fs::path *reg_write_file);
  void init_mem(fs::path *mem_init_file, fs::path *mem_write_file);
  void init_instruction_set();
  void init_registers_map();

public:
  const memory &get_mem();
  const memory &get_reg();
  int get_pc();
  int parse_instruction(
      const std::string
          &instruction); // returns the machine code for the instruction
  bool end_of_program();
  void execute();
  void
  read_program(fs::path &text,
               fs::path *mem_init_file = nullptr,
               fs::path *mem_write_file = nullptr,
               fs::path *reg_init_file = nullptr,
               fs::path *reg_write_file = nullptr); // reads a file and adds instructions
                                          // to the instructions vector
  const std::vector<std::string> &get_instructions();
  riscv();
};
