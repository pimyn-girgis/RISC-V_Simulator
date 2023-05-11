#pragma once


#ifndef PARSER_H
#define PARSER_H
#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <array>

using namespace std;

/// AW: Header file to include our parser declarations for good repo hygiene
/// you could make a class to encapsulate the parser if needed, see how this may/may not help you


map<const char *, int>Set_Instruction_Set();
map<char*, int*> set_registers();
vector<string> Get_Instructions();
map<char*, int> Get_Labels(vector<string>& instruction_string);
void Translate_Instructions(vector<string>& instruction_string, map<string, int>& instruction_set, map<char*, int*> registers);

int parse_instruction(const string *instruction);

//	Instruction parsers Declarations	//
void LUI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void AUIPC(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void JAL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void JALR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BEQ(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BNE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BLT(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BGE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BLTU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void BGEU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers, map<char*, int> labels);
void LB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void LH(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void LW(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void LBU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void LHU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SH(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SW(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void ADDI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLTI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLTIU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void XORI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void ORI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void ANDI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLLI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SRLI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SRAI(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void ADD(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SUB(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLT(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SLTU(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void XOR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SRL(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void SRA(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void OR(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void AND(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);
void TERMINATE(char* res, char* str, const char* delim, char* nextInstruction, map<char*, int*> registers);

// eof Fx Declarations	//
#endif // !PARSER_H
