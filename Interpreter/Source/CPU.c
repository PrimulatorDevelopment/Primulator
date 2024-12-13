#include <stdlib.h>
#include <stdio.h>
#include "CPU.h"

// Le global scope
CPU* cpu;

CPU* initilize_CPU(){
    cpu = (CPU*) malloc(sizeof(CPU));
    cpu->registers = initialize_registers();
    cpu->memory = initialize_ram();

    cpu->registers[0] = 0;
    return cpu;
}

void destory_CPU(CPU** processor){
    if (processor == NULL)
        return;
    
    destroy_memory(&((*processor)->memory));
    destroy_registers(&((*processor)->registers));
    free(*processor);
    processor = NULL;
}


void add(int rd, int rs1, int rs2){
    if (rd == 0) return;
    
    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] + (int32_t)cpu->registers[rs2]);
}
void addi(int rd, int rs1, int16_t imm){
    if (rd == 0) return;

    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] + (int32_t)imm);
}
void neg(int rd, int rs1){
    if (rd == 0) return;
    
    cpu->registers[rd] = (uint32_t) -((int32_t)cpu->registers[rs1]);
}
void sub(int rd, int rs1, int rs2){
    if (rd == 0) return;
    
    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] - (int32_t)cpu->registers[rs2]);
}
void mul(int rd, int rs1, int rs2){
    if (rd == 0) return;

    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] * (int32_t)cpu->registers[rs2]);
}
void divi(int rd, int rs1, int rs2){
    if (rd == 0) return;

    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] / (int32_t)cpu->registers[rs2]);
}
void rem(int rd, int rs1, int rs2){
    if (rd == 0) return;

    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] % (int32_t)cpu->registers[rs2]);
}



