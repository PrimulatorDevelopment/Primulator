#include "Register.h"

uint32_t* initialize_registers(){
    uint32_t* registers = calloc(REG_COUNT, sizeof(uint32_t));
    return registers;
}
void destroy_registers(uint32_t** reg){
    if (reg == NULL)
        return;
    
    free(*reg);
    reg = NULL;
}
