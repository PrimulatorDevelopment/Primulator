#include <stdlib.h>
#include <stdint.h>

#pragma region definitions
#define TRUE 1
#define FALSE 0

#define MEM_SIZE     0x100000                       // 10MB

#define IO_SIZE       0x40
#define CODE_SIZE     0x2000
#define DATA_SIZE     0x2000
#define HEAP_SIZE     0x10000
#define STACK_SIZE    0x10000 - IO_SIZE

#define CODE_OFFSET  0                               // .text  -> 8kb  large
#define DATA_OFFSET  CODE_OFFSET + CODE_SIZE         // .data  -> 8kb  large
#define HEAP_OFFSET  DATA_OFFSET + DATA_SIZE         // .heap  -> 64kb large
#define STACK_OFFSET HEAP_OFFSET + HEAP_SIZE         // .stack -> 64kb - IO_SIZE large
#define INPUT_OFFSET STACK_OFFSET + STACK_SIZE       // .input -> 64b  large
#pragma endregion

uint8_t* initialize_ram();
void destroy_memory(uint8_t** mem);