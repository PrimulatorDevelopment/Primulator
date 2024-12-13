#include <stdlib.h>
#include <stdio.h>
#include "CPU.h"

int main(void){
    CPU* cpu = initilize_CPU();
    addi(1, 0, 5); // reg 1 = 5
    addi(2, 0, -3); // reg 2 = -3
    add(3, 1, 2); // reg 3 = reg 1 + reg 2
    printf("%d\n", (int32_t) cpu->registers[3]);

    destory_CPU(&cpu);
}
