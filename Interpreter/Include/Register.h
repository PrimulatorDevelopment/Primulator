#include <stdlib.h>
#include <stdint.h>

#pragma region definitions
#define REG_COUNT        32
#define PROGRAM_COUNTER  0
#define STACK_POINTER    1

#pragma endregion

uint32_t* initialize_registers();
void destroy_registers(uint32_t** reg);