#pragma once

#include <stdlib.h>
#include <stdint.h>

#pragma region definitions
#define TRUE 1
#define FALSE 0

#define MEM_SIZE     0x100000  // 10MB

#define IO_START     0x0
#define IO_SIZE     0xFF //256 Bytes

#define STACK_START IO_SIZE + 1 //Starts after IO and grows down

#pragma endregion

uint8_t* initialize_ram();
void destroy_memory(uint8_t** mem);