#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <bitset>
#include <array>
#include "genUtils.h"
#include "memory.h"

struct instruction {
    std::string assembly;
    int machine;
    instruction(const std::string &assembly, const int machine);
};

class riscv
{
private:
    memory mem;
    memory reg;
    std::unordered_map<std::string, int> instruction_set;
    std::vector<instruction> instructions;
	std::unordered_map<std::string, int> registers;
    std::unordered_map <std::string, int> labels; // word addressable relative to start of the program
    void set_instruction_set(); // sets the instruction set
    void read_line(const std::string &line); // adds an instruction to the instructions vector
    void parse_program(); // parses the instructions vector and adds the machine code to it
    int parse_operands(int machine, char *operands[3], int inst_num); // returns the machine code for the operands
    void m_lui();
    void m_auipc();
    void m_jal();
    void m_jalr();
    void branch();
    void m_lb();
    void m_lh();
    void m_lw();
    void m_lbu();
    void m_lhu();
    void m_sb();
    void m_sh();
    void m_sw();
    void m_addi();
    void m_slti();
    void m_sltiu();
    void m_xori();
    void m_ori();
    void m_andi();
    void m_slli();
    void m_srli();
    void m_srai();
    void m_add();
    void m_sub();
    void m_sll();
    void m_slt();
    void m_sltu();
    void m_xor();
    void m_srl();
    void m_sra();
    void m_or();
    void m_and();
    void m_terminate();
public:
    int parse_instruction(const std::string &instruction); // returns the machine code for the instruction
    void read_program(const std::string &filename); // reads a file and adds instructions to the instructions vector
    const std::vector<instruction> &get_instructions();
    riscv(fs::path *mem_init_file, fs::path *mem_write_file,
	  fs::path *reg_init_file, fs::path *reg_write_file);
};
