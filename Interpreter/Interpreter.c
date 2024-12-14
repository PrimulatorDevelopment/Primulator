#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Executable.h>
#include <CPU.h>

CPU* interpreter;

void run_program(Program* program) {
    interpreter->registers[PROGRAM_COUNTER] = program->elf_header.e_entry;
    uint64_t entry_point = interpreter->registers[PROGRAM_COUNTER];

    for(int i = 0; i< 40; i += 4){
        printf("\n");

        uint16_t op_code = program->virtual_memory[entry_point + i] & 0x7F; // 0b01111111
        uint8_t rd = ((program->virtual_memory[entry_point + i] >> 7) | (program->virtual_memory[entry_point + i + 1] << 1)) & 0x1F;
        switch (op_code) {
            case R_TYPE:
                // R-type instructions
                printf("%d, R-type instruction\n", rd);
                break;

            case I_TYPE:
            case OPCODE_LW:
                // I-type instructions
                printf("%d, I-type instruction\n", rd);
                break;

            case OPCODE_SW:
                // S-type instructions
                printf("%d, S-type instruction\n", rd);
                break;

            default:
                printf("Unknown instruction\n");
                break;
        }
    }

    for(int i = program->min_address; i > 0 ; i--){
        //print_binary(interpreter->memory[i]);
        //printf("\n");
    }


}



int main() {
    interpreter = initilize_CPU();
    Program* program = load_program("executables/EXEC.elf");

    call_instruction(R_TYPE, combine(0, 0), 1, zero, 3);
    printf("%d\n", interpreter->registers[1]);
    run_program(program);
    

    return 0;
}
