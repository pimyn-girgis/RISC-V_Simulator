#include "riscv.h"
#include "genUtils.h"

//sorry will put at top lol
int riscv::get_pc()
{
    return pc << 2;
}

void riscv::init_reg(fs::path *reg_init_file, fs::path *reg_write_file)
{
  if (reg_init_file != nullptr && reg_write_file != nullptr) {
    reg = memory(0x00000020, reg_init_file, reg_write_file); // 32 registers
    reg.init_memory(reg.parse_init_file());
  } else {
    reg = memory(0x00000020);
  }
  reg.set_constantAddress(0, 0);
}

void riscv::init_mem(fs::path *mem_init_file, fs::path *mem_write_file) {

  if (mem_init_file != nullptr && mem_write_file != nullptr) {
    mem = memory(0xffffffff, mem_init_file, mem_write_file); // 4GB memory
    mem.init_memory(mem.parse_init_file());
  } else {
    mem = memory(0xffffffff);
  }
  mem.set_sectionAddresses(new std::vector<std::pair<const char *, size_t>>(
      {{"text", 0x00000000}, {"data", 0x00400000}, {"stack", 0x00800000}}));
      // text starts at 0MB, data at 4MB, stack at 8MB
  pc = 0;
}

void riscv::init_instruction_set()
{
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
      {"ebreak", 0x00100073}};
}

void riscv::init_registers_map()
{
  registers_map = {
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
      {"x28", 28}, {"x29", 29}, {"x30", 30}, {"x31", 31}};
}

riscv::riscv() {
  init_registers_map();
  init_instruction_set();
}

int riscv::parse_operands(int machine, char *operands[3], int inst_num) {
    int opcode = genUtils::get_bits(machine, 0, 6);
    // parse operands and set machine code accordingly
    switch (opcode) {
    case 0x67: // jalr
    case 0x03: // load
      // jalr and load instructions have the same format
      machine = set_rd(machine, registers_map[operands[0]]);
      machine = set_imm(machine, atoi(operands[1]));
      machine = set_rs1(machine, registers_map[operands[2]]);
      break;
    case 0x13: // imm
      machine = set_rd(machine, registers_map[operands[0]]);
      machine = set_rs1(machine, registers_map[operands[1]]);
      machine = set_imm(machine, atoi(operands[2]));
      break;
    case 0x23: // store
      machine = set_rs1(machine, registers_map[operands[0]]);
      machine = set_sep_imm(machine, atoi(operands[1]));
      machine = set_rs2(machine, registers_map[operands[2]]);
      break;
    case 0x63: // branch
      machine = set_rs1(machine, registers_map[operands[0]]);
      machine = set_rs2(machine, registers_map[operands[1]]);
      machine = set_sep_imm(machine, labels[operands[2]] - inst_num - 1);
      break;
    case 0x33: // rtype
      machine = set_rd(machine, registers_map[operands[0]]);
      machine = set_rs1(machine, registers_map[operands[1]]);
      machine = set_rs2(machine, registers_map[operands[2]]);
      break;
    case 0x6f: // jal
      machine = set_rd(machine, registers_map[operands[0]]);
      machine = set_upp_imm(machine, labels[operands[1]] - inst_num - 1);
      break;
    case 0x37: // lui
    case 0x17: // auipc
      machine = set_rd(machine, registers_map[operands[0]]);
      machine = set_upp_imm(machine, atoi(operands[1]));
      break;
    case 0x0f: // fence
    case 0x73: // ecall, ebreak
      break;
    default:
      std::cout << "Error: invalid instruction opcode: " << opcode << '\n';
      break;
    }

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
  // if there are more, the rest are ignored (helps with comments)
  for (int i = 0; i < 3; i++) {
    operands[i] = strtok(NULL, delim);
  }

  auto it = instruction_set.find(mnemonic);
  if (it != instruction_set.end()) {
        machine = parse_operands(it->second, operands, &instruction - &instructions[0]);
  } else {
    std::cout << "Error: invalid instruction mnemonic: " << mnemonic << '\n';
  }

  free(str);
  return machine;
}

void riscv::parse_program() {
  for (auto &instruction : instructions) {
    mem.write_to_memory(pc++ << 2, parse_instruction(instruction), 4);
  }
  pc = 0;
}

void riscv::read_program(fs::path &text,
                         fs::path *mem_init_file,
                         fs::path *mem_write_file,
                         fs::path *reg_init_file,
                         fs::path *reg_write_file) {
  std::ifstream file;

  file.open(text);
  if(file.is_open())
  {
  std::string line;
  while (!file.eof()) {
    getline(file, line);
    read_line(line);
  }
  }
  file.close();

  init_mem(mem_init_file, mem_write_file);
  init_reg(reg_init_file, reg_write_file);

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
    instructions.emplace_back(line);
  }
}

const std::vector<std::string> &riscv::get_instructions() {
    return instructions;
}

void riscv::load(int instruction)
{
  int loop_len = 0;
  bool extend = false;
  
  switch (get_funct3(instruction)) {
    case 0b000: // lb
      loop_len = 1;
      break;
    case 0b001: // lh
      loop_len = 2;
      break;
    case 0b010: // lw
      loop_len = 4;
      break;
    case 0b100: // lbu
      loop_len = 1;
      extend = true;
      break;
    case 0b101: // lhu
      loop_len = 2;
      extend = true;
      break;
  }

  int write_value = 0;
  const int load_addr = reg.read_from_memory(get_rs1(instruction)) +
                  genUtils::sign_extend(get_imm(instruction), 12);
  
  for (int i = 0; i < loop_len; i++) {
    write_value |= mem.read_from_memory(load_addr + i) << (8 * i);
  }
  reg.write_to_memory(get_rd(instruction),
                      extend ? genUtils::sign_extend(write_value, loop_len * 8)
                             : write_value);
}

//ADDI SLTI SLTIU XORI ORI ANDI SLLI SRLI SRAI
void riscv::imm(int instruction)
{
  int rd  = get_rd(instruction);
  int rs1 = reg.read_from_memory(get_rs1(instruction));
  int imm = genUtils::sign_extend(get_imm(instruction), 12);
  int shamt = get_shamt(instruction);

  int write_value = 0;
  switch (get_funct3(instruction)) {
    case 0b000: // addi
      write_value = rs1 + imm;
      break;
    case 0b010: // slti
      write_value = rs1 < imm;
      break;
    case 0b011: // sltiu
      write_value = (unsigned int)rs1 < (unsigned int)imm;
      break;
    case 0b100: // xori
      write_value = rs1 ^ imm;
      break;
    case 0b110: // ori
      write_value = rs1 | imm;
      break;
    case 0b111: // andi
      write_value = rs1 & imm;
      break;
    case 0b001: // slli
      write_value = rs1 << imm;
      break;
    case 0b101: // srli srai
      write_value = rs1 >> shamt;
      if (get_funct7(instruction)) { //srai
        write_value = genUtils::sign_extend(write_value, 32 - shamt);
      }
      break;
  }
  reg.write_to_memory(rd, write_value);
}

void riscv::utype(int instruction)
{
  int rd  = get_rd(instruction);
  int write_value = get_upp_imm(instruction) << 12;

  switch (get_opcode(instruction)) {
    case 0b0110111: // lui
      reg.write_to_memory(rd, write_value);
      break;
    case 0b0010111: // auipc
      reg.write_to_memory(rd, (pc << 2) + write_value);
      break;
  }
}

void riscv::btype(int instruction) 
{
  int rs1 = reg.read_from_memory(get_rs1(instruction));
  int rs2 = reg.read_from_memory(get_rs2(instruction));
  bool branch = false;

  switch (get_funct3(instruction)) {
    case 0b000: // beq
      branch = (rs1 == rs2);
      break;
    case 0b001: // bne
      branch = (rs1 != rs2);
      break;
    case 0b100: // blt
      branch = (rs1 < rs2);
      break;
    case 0b101: // bge
      branch = (rs1 >= rs2);
      break;
    case 0b110: // bltu
      branch = ((unsigned int)rs1 < (unsigned int)rs2);
      break;
    case 0b111: // bgeu
      branch = ((unsigned int)rs1 >= (unsigned int)rs2);
      break;
  }

  if (branch) {
    pc += genUtils::sign_extend(get_sep_imm(instruction), 12);
  }
}

void riscv::jtype(int instruction) {
  reg.write_to_memory(get_rd(instruction), (pc + 1) << 2);
  pc += genUtils::sign_extend(get_upp_imm(instruction), 20);
}

void riscv::itype(int instruction) {
  switch (get_opcode(instruction)) {
    case 0b0000011: // lb lh lw lbu lhu
      load(instruction);
      break;
    case 0b0010011: // addi slti sltiu xori ori andi slli srli srai
      imm(instruction);
      break;
  }
}

void riscv::rtype(int instruction) { // ADD SUB SLL SLT SLTU XOR SRL SRA OR AND
  int rd = get_rd(instruction);
  int rs1 = reg.read_from_memory(get_rs1(instruction));
  int rs2 = reg.read_from_memory(get_rs2(instruction));
  int write_value = 0;
  switch (get_funct3(instruction)) {
    case 0b000: // add sub
      write_value = rs1 + rs2;
      if (get_funct7(instruction)) { // sub
        write_value = rs1 - rs2;
      }
      break;
    case 0b001: // sll
      write_value = rs1 << rs2;
      break;
    case 0b010: // slt
      write_value = rs1 < rs2;
      break;
    case 0b011: // sltu
      write_value = (unsigned int)rs1 < (unsigned int)rs2;
      break;
    case 0b100: // xor
      write_value = rs1 ^ rs2;
      break;
    case 0b101: // srl sra
      write_value = rs1 >> rs2;
      if (get_funct7(instruction)) { // sra
        write_value = genUtils::sign_extend(write_value, 32 - rs2);
      }
      break;
    case 0b110: // or
      write_value = rs1 | rs2;
      break;
    case 0b111: // and
      write_value = rs1 & rs2;
      break;
  }
  reg.write_to_memory(rd, write_value);
}

void riscv::stype(int instruction) {
  int write_value = reg.read_from_memory(get_rs1(instruction));
  int address = reg.read_from_memory(get_rs2(instruction)) +
                genUtils::sign_extend(get_sep_imm(instruction), 12);
  int byte_count = 0;

  switch (get_funct3(instruction)) {
    case 0b000: // sb
      byte_count = 1;
      break;
    case 0b001: // sh
      byte_count = 2;
      break;
    case 0b010: // sw
      byte_count = 4;
      break;
  }
      mem.write_to_memory(address, write_value, byte_count);
      std::cout << "wrote " << mem.read_from_memory(address, byte_count) << " to " << address << std::endl;
}

void riscv::execute() {
  int instruction = mem.read_from_memory(pc << 2, 4);

  switch(get_opcode(instruction)) {
    case 0b0110111: // lui
    case 0b0010111: // auipc
      utype(instruction);
      break;
    case 0b1101111: // jal
      jtype(instruction);
      break;
    case 0b1100111: // jalr
      reg.write_to_memory(get_rd(instruction), (pc + 1) << 2);
      pc = (reg.read_from_memory(get_rs1(instruction)) + genUtils::sign_extend(get_imm(instruction), 12));
      // pc = (rs1 + imm) & ~1
      // rd = pc + 4
      break;
    case 0b1100011: // btype
      btype(instruction);
      break;
    case 0b0000011: // load
    case 0b0010011: // imm
      itype(instruction);
      break;
    case 0b0100011: // store
      stype(instruction);
      break;
    case 0b0110011: // reg
      rtype(instruction);
      break;
    case 0b0001111: // fence
    case 0b1110011: // system
    // terminate program
      pc = -1;
      break;
  }

  // std::cout << std::left << std::setw(20) << instructions[pc];
  for(int i = 0; i < 32; i++) {
    std::cout << reg.read_from_memory(i) << " ";
  }

  std::cout << std::endl;

  ++pc;
}

int riscv::get_rd(int instruction) {
  return genUtils::get_bits(instruction, 7, 11);
}

int riscv::get_rs1(int instruction) {
  return genUtils::get_bits(instruction, 15, 19);
}

int riscv::get_rs2(int instruction) {
  return genUtils::get_bits(instruction, 20, 24);
}

int riscv::get_imm(int instruction) {
  return genUtils::get_bits(instruction, 20, 31);
}

int riscv::get_shamt(int instruction) {
  return genUtils::get_bits(instruction, 20, 24);
}

int riscv::get_sep_imm(int instruction) {
  return genUtils::get_bits(instruction, 7, 11) |
         (genUtils::get_bits(instruction, 25, 31) << 5);
}

int riscv::get_upp_imm(int instruction) {
  return genUtils::get_bits(instruction, 12, 31);
}

int riscv::set_rd(int instruction, int value) {
  return genUtils::set_bits(instruction, 7, 11, value);
}

int riscv::set_rs1(int instruction, int value) {
  return genUtils::set_bits(instruction, 15, 19, value);
}

int riscv::set_rs2(int instruction, int value) {
  return genUtils::set_bits(instruction, 20, 24, value);
}

int riscv::set_imm(int instruction, int value) {
  return genUtils::set_bits(instruction, 20, 31, value);
}

int riscv::set_shamt(int instruction, int value) {
  return genUtils::set_bits(instruction, 20, 24, value);
}

int riscv::set_sep_imm(int instruction, int value) {
  return genUtils::set_bits(instruction, 7, 11, value) |
         (genUtils::set_bits(instruction, 25, 31, value >> 5));
}

int riscv::get_opcode(int instruction) {
  return genUtils::get_bits(instruction, 0, 6);
}

int riscv::get_funct3(int instruction) {
  return genUtils::get_bits(instruction, 12, 14);
}

int riscv::get_funct7(int instruction) {
  return genUtils::get_bits(instruction, 25, 31);
}

int riscv::set_opcode(int instruction, int value) {
  return genUtils::set_bits(instruction, 0, 6, value);
}

int riscv::set_funct3(int instruction, int value) {
  return genUtils::set_bits(instruction, 12, 14, value);
}

int riscv::set_funct7(int instruction, int value) {
  return genUtils::set_bits(instruction, 25, 31, value);
}

int riscv::set_upp_imm(int instruction, int value) {
  return genUtils::set_bits(instruction, 12, 31, value);
}
bool riscv::end_of_program() {
  return pc == -1 || pc >= instructions.size();
}

const memory& riscv::get_mem() {
  return mem;
}

const memory& riscv::get_reg() {
  return reg;
}
