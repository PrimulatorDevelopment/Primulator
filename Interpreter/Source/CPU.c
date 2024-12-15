#include <stdlib.h>
#include <stdio.h>
#include <Executable.h>
#include <CPU.h>

// Le global scope
CPU* cpu;

CPU* initilize_CPU(){
    cpu = (CPU*) malloc(sizeof(CPU));
    cpu->registers = initialize_registers();
    cpu->memory = initialize_ram();

    cpu->registers[0] = 0; // always zero register
    cpu->running = 1;

    return cpu;
}

CThread* initilize_Thread(void* function){
    CThread* pThread = NULL;
    for (int i = 0; i < MAX_THREADS; i++){
        if  (cpu->threads[i] == NULL){
            cpu->threads[i] = create_Thread(function);
            pThread = cpu->threads[i];
            break;
        }
    }

    return pThread; // can return null when thread slots are full
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
void xor(int rd, int rs1, int rs2){
    if (rd == 0) return;
    
    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] ^ (int32_t)cpu->registers[rs2]);
}
void or(int rd, int rs1, int rs2){
    if (rd == 0) return;
    
    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] | (int32_t)cpu->registers[rs2]);
}
void and(int rd, int rs1, int rs2){
    if (rd == 0) return;
    
    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] & (int32_t)cpu->registers[rs2]);
}
void addi(int rd, int rs1, int16_t imm){
    if (rd == 0) return;

    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[rs1] + (int32_t)imm);
    printf("addi %s, %s, %d\n", get_register(rd), get_register(rs1), (int32_t)imm);
}
void li(int rd, int16_t imm, char _){
    if (rd == 0) return;

    cpu->registers[rd] = (uint32_t) ((int32_t)cpu->registers[zero] + (int32_t)imm);
}
void sh(int rs1, int rs2, int16_t imm){
    cpu->memory[rs1+imm] = rs2;
    printf("sh %s, %d(%s)\n", get_register(rs2), (int16_t)imm, get_register(rs1));
}
void neg(int rd, int rs1, char _){
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



