#include <cstring>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <unordered_map>

int set_bits(int num, int start, int end, int value) {
	value &= (1 << (end - start + 1)) - 1;
	int mask = (1 << (end - start + 1)) - 1;
	return (num & ~(mask << start)) | (value << start);
}

std::unordered_map<std::string, int>  instruction_set = {
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

std::unordered_map<std::string, int> registers = {
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
      {"x28", 28}, {"x29", 29}, {"x30", 30}, {"x31", 31},
  };

std::unordered_map<std::string, int> labels = {
	  {"label", 0x0000037f},
  };

int main() {
      const char *delim = " ,()";
      int machine = 0;

      char *str;
      strcpy(str, "beq x1, x2, label");

      char *mnemonic = strtok(str, delim); // mnemonic is the first token
      char *operands[3];                   // operands are the next tokens
      // assumes 3 operands, if there are less, the rest are NULL
      // if there are more, the rest are ignored
      for (int i = 0; i < 3; i++) {
        operands[i] = strtok(NULL, delim);
      }

      machine = set_bits(machine, 0, 6, instruction_set[mnemonic]);
      machine = set_bits(machine, 15, 19, registers[operands[0]]);
      machine = set_bits(machine, 20, 24, registers[operands[1]]);
      machine = set_bits(machine, 7, 11, labels[operands[2]]);
      machine = set_bits(machine, 25, 31, labels[operands[2]] >> 5);

      std::cout << std::bitset<32>(labels[operands[2]]) << std::endl << std::bitset<32>(machine) << std::endl << std::hex << machine << std::endl;
}
