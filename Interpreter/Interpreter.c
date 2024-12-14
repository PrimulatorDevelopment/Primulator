#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "CPU.h"
#include "Input.h"

int main(void){
    CPU* cpu = initilize_CPU();
    //CThread* tInput = initilize_Thread(input_thread);

    while (cpu->running){

    }

    destory_CPU(&cpu);
}
