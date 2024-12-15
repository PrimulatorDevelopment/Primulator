#include "Register.h"

const char *register_names[32] = {
        "zero", "ra", "sp", "gp", "tp",
        "t0", "t1", "t2", "s0", "s1",
        "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
        "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11",
        "t3", "t4", "t5", "t6"
    };

uint32_t* initialize_registers(){
    uint32_t* registers = calloc(REG_COUNT, sizeof(uint32_t));
    return registers;
}

const char* get_register(int rs){
    return register_names[rs];
}

void destroy_registers(uint32_t** reg){
    if (reg == NULL)
        return;
    
    free(*reg);
    reg = NULL;
}
