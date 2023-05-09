#include "riscv.h"

instruction::instruction(const std::string &assembly, const int machine)
    : assembly(assembly), machine(machine) {}

riscv::riscv() {
  instruction_set = {
      {"lui", 0x00000037},    {"auipc", 0x00000017}, {"jal", 0x0000006f},
      {"jalr", 0x00000067},   {"beq", 0x00000063},   {"bne", 0x00001063},
      {"blt", 0x00004063},    {"bge", 0x00005063},   {"bltu", 0x00006063},
      {"bgeu", 0x00007063},   {"lb", 0x00000003},    {"lh", 0x00001003},
      {"lw", 0x00002003},     {"lbu", 0x00004003},   {"lhu", 0x00005003},
      {"sb", 0x00000023},     {"sh", 0x00001023},    {"sw", 0x00002023},
      {"addi", 0x00000013},   {"slti", 0x00002013},  {"sltiu", 0x00003013},
      {"xori", 0x00004013},   {"ori", 0x00006013},   {"andi", 0x00007013},
      {"slli", 0x00001013},   {"srli", 0x00005013},  {"srai", 0x40005013},
      {"add", 0x00000033},    {"sub", 0x40000033},   {"sll", 0x00001033},
      {"slt", 0x00002033},    {"sltu", 0x00003033},  {"xor", 0x00004033},
      {"srl", 0x00005033},    {"sra", 0x40005033},   {"or", 0x00006033},
      {"and", 0x00007033},    {"fence", 0x0000000f}, {"ecall", 0x00000073},
      {"ebreak", 0x00100073},
  };
  registers = {
      {"zero", 0}, {"ra", 1},   {"sp", 2},   {"gp", 3},   {"tp", 4},
      {"t0", 5},   {"t1", 6},   {"t2", 7},   {"s0", 8},   {"s1", 9},
      {"a0", 10},  {"a1", 11},  {"a2", 12},  {"a3", 13},  {"a4", 14},
      {"a5", 15},  {"a6", 16},  {"a7", 17},  {"s2", 18},  {"s3", 19},
      {"s4", 20},  {"s5", 21},  {"s6", 22},  {"s7", 23},  {"s8", 24},
      {"s9", 25},  {"s10", 26}, {"s11", 27}, {"t3", 28},  {"t4", 29},
      {"t5", 30},  {"t6", 31},  {"x0", 0},   {"x1", 1},   {"x2", 2},
      {"x3", 3},   {"x4", 4},   {"x5", 5},   {"x6", 6},   {"x7", 7},
      {"x8", 8},   {"x9", 9},   {"x10", 10}, {"x11", 11}, {"x12", 12},
      {"x13", 13}, {"x14", 14}, {"x15", 15}, {"x16", 16}, {"x17", 17},
      {"x18", 18}, {"x19", 19}, {"x20", 20}, {"x21", 21}, {"x22", 22},
      {"x23", 23}, {"x24", 24}, {"x25", 25}, {"x26", 26}, {"x27", 27},
      {"x28", 28}, {"x29", 29}, {"x30", 30}, {"x31", 31}, {"pc", 32},
  };
  
}

int riscv::parse_operands(int machine, char *operands[3], int inst_num) {
    int opcode = genUtils::get_bits(machine, 0, 6);
    // parse operands and set machine code accordingly
    switch (opcode) {
    case 0x67: // jalr
    case 0x03: // load
      // jalr and load instructions have the same format
      machine = genUtils::set_bits(machine, 7, 11, registers[operands[0]]);
      machine = genUtils::set_bits(machine, 20, 31, atoi(operands[1]));
      machine = genUtils::set_bits(machine, 15, 19, registers[operands[2]]);
      break;
    case 0x13: // imm
      machine = genUtils::set_bits(machine, 7, 11, registers[operands[0]]);
      machine = genUtils::set_bits(machine, 15, 19, registers[operands[1]]);
      machine = genUtils::set_bits(machine, 20, 31, atoi(operands[2]));
      break;
    case 0x23: // store
      machine = genUtils::set_bits(machine, 15, 19, registers[operands[0]]);
      machine = genUtils::set_bits(machine, 20, 24, registers[operands[2]]);
      machine = genUtils::set_bits(machine, 7, 11, atoi(operands[1]));
      machine = genUtils::set_bits(machine, 25, 31, atoi(operands[1]) >> 5);
      break;
    case 0x63: // branch
      machine = genUtils::set_bits(machine, 15, 19, registers[operands[0]]);
      machine = genUtils::set_bits(machine, 20, 24, registers[operands[1]]);
      machine = genUtils::set_bits(machine, 7, 11, labels[operands[2]]);
      machine = genUtils::set_bits(machine, 25, 31, labels[operands[2]] >> 5);
      break;
    case 0x33: // rtype
      machine = genUtils::set_bits(machine, 7, 11, registers[operands[0]]);
      machine = genUtils::set_bits(machine, 15, 19, registers[operands[1]]);
      machine = genUtils::set_bits(machine, 20, 24, registers[operands[2]]);
      break;
    case 0x6f: // jal
      machine = genUtils::set_bits(machine, 7, 11, registers[operands[0]]);
      machine = genUtils::set_bits(machine, 12, 19, labels[operands[1]]);
      break;
    case 0x37: // lui
    case 0x17: // auipc
      machine = genUtils::set_bits(machine, 7, 11, registers[operands[0]]);
      machine = genUtils::set_bits(machine, 12, 31, atoi(operands[1]));
      break;
    case 0x0f: // fence
    case 0x73: // ecall, ebreak
      break;
    default:
      std::cout << "Error: invalid instruction opcode: " << opcode << '\n';
      break;
    }

    std::cout << std::bitset<32> (machine) << '\n';
    return machine;
}

int riscv::parse_instruction(const std::string &instruction) {
  const char *delim = " ,()";
  int machine = 0;

  char *str = (char *)malloc(sizeof(char) * instruction.size() + 1);
  memcpy(str, instruction.c_str(), instruction.size() + 1);

  char *mnemonic = strtok(str, delim); // mnemonic is the first token
  char *operands[3];                   // operands are the next tokens
  // assumes 3 operands, if there are less, the rest are NULL
  // if there are more, the rest are ignored
  for (int i = 0; i < 3; i++) {
    operands[i] = strtok(NULL, delim);
  }

  auto it = instruction_set.find(mnemonic);
  if (it != instruction_set.end()) {
        machine = parse_operands(it->second, operands);
  } else {
    std::cout << "Error: invalid instruction mnemonic: " << mnemonic << '\n';
  }

  free(str);
  return machine;
}

void riscv::parse_program() {
  for (auto &instruction : instructions) {
    instruction.machine = parse_instruction(instruction.assembly);
  }
}

void riscv::read_program(const std::string &filename) {
  std::ifstream file;

  file.open(filename);
  std::string line;
  while (!file.eof()) {
    getline(file, line);
    read_line(line);
  }
  file.close();
  parse_program();
}

void riscv::read_line(const std::string &line) {
  const char *whitespace = " \t\n\r\f\v";

  if (line.size() == 0 // if line is empty
      || line.find_first_not_of(whitespace) ==
             std::string::npos // if line is just whitespace
      || line[0] == '#')       // if line is a comment
    return;

  // if line contains a label
  auto label_pos = line.find(':');
  if (label_pos != std::string::npos) {
    std::string label = line.substr(0, label_pos);
    labels[label] = instructions.size();
    read_line(line.substr(label_pos + 1));
  } else {
    // machine code initialized to 0 to make sure that the labels are defined
    // before they are used
    instructions.emplace_back(line, 0);
  }
}

void riscv::set_instruction_set() {}
const std::vector<instruction> &riscv::get_instructions() {
    return instructions;
}

void riscv::branch() {
  int instruction = instructions[0].machine;
  int branch_type = genUtils::get_bits(instruction, 12, 14);
  switch (branch_type) {
    case 000: // beq
      break;
  }
}
