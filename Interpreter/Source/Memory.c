#include "Memory.h"

uint8_t* initialize_ram(){
    uint8_t* RAM = calloc(MEM_SIZE, sizeof(uint8_t));
    return RAM;
}

void destroy_memory(uint8_t** mem){
    if (mem == NULL)
        return;
    
    free(*mem);
    mem = NULL;
}