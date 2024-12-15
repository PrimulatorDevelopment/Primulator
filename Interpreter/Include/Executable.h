#pragma once
#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <CPU.h>

#define MAGIC_RAM 0x11221416

typedef struct Program{
    const char *filename;
    Elf64_Ehdr elf_header;
    uint8_t* virtual_memory; // not really but sure lol
    uint64_t min_address;
} Program;


Program* load_program(const char *filename);

#pragma region op codes

#define R_TYPE    51  // 0110011
#define I_TYPE   19  // 0010011
#define S_TYPE   35  // 0100011 3

#define OPCODE_LW     3   // 0000011
#define OPCODE_SW     35  // 0100011

#pragma endregion

#pragma region func codes

#define combine(num1, num2) (num1 << 8) | num2
#define extracto(num1) (combined >> 8) & 0xFF
#define extractt(num2) num2 & 0xFF

#define fADD combine(0, 0)
#define fSUB combine(0, 32)
#define fXOR combine(4, 0)
#define fOR combine(6, 0)
#define fAND combine(7, 0)

#define fADDI combine(0, 0)
#define fXORI combine(4, 0)
#define fORI combine(6, 0)
#define fANDI combine(7, 0)

#define fSH combine(1, 35)

#pragma endregion

int resolve_type(int type);
int resolve_func(int func);

extern void (*instruction_table[4][4])(int, int, int);
void call_instruction(int type, int func, int a, int b, int c);