#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Executable.h>
#include <CPU.h>

CPU* interpreter;
uint64_t min_address = 0;

int main() {
    // Load ELF file into memory
    interpreter = initilize_CPU();
    Program* program = load_program("executables/EXEC.elf");

    // Execute the loaded program
    run_program(interpreter, program);

    return 0;
}
