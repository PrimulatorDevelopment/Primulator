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
void run_program(CPU* interpreter, Program* program);


#pragma region op codes

#define R_TYPE    51  // 0110011

#define I_TYPE   19  // 0010011

#define OPCODE_LW     3   // 0000011
#define OPCODE_SW     35  // 0100011

#pragma endregion