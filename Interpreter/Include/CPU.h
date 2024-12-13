#include <stdlib.h>
#include <stdio.h>
#include "Memory.h"
#include "Register.h"

typedef struct CPU
{
    uint32_t* registers;
    uint8_t* memory;
} CPU;


CPU* initilize_CPU();
void destory_CPU(CPU** processor);


#pragma region cpu instructions
void add  (int rd, int rs1, int rs2);
void addi (int rd, int rs1, int16_t imm);
void divi (int rd, int rs1, int rs2);
void neg  (int rd, int rs1);
void sub  (int rd, int rs1, int rs2);
void mul  (int rd, int rs1, int rs2);
void rem  (int rd, int rs1, int rs2);
#pragma endregion