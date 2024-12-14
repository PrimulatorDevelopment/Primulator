#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Threading.h"
#include "Memory.h"
#include "Register.h"

#define MAX_THREADS 4

typedef struct CPU
{
    uint32_t* registers;
    uint8_t* memory;

    CThread* threads[MAX_THREADS];

    char running;
} CPU;


CPU* initilize_CPU();
CThread* initilize_Thread(void* function);
void destory_CPU(CPU** processor);

#pragma region cpu instructions
void add  (int rd, int rs1, int rs2);
void addi (int rd, int rs1, int16_t imm);
void li   (int rd, int16_t imm, char _);
void divi (int rd, int rs1, int rs2);
void neg  (int rd, int rs1, char _);
void sub  (int rd, int rs1, int rs2);
void mul  (int rd, int rs1, int rs2);
void rem  (int rd, int rs1, int rs2);
#pragma endregion