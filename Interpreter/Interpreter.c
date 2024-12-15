#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Executable.h>
#include <CPU.h>

CPU* interpreter;

void run_program(Program* program) {
    interpreter->registers[PROGRAM_COUNTER] = program->elf_header.e_entry;
    interpreter->memory = program->virtual_memory;
    uint64_t entry_point = interpreter->registers[PROGRAM_COUNTER];

    for(int i = 0; i< 40; i += 4){
        printf("\n");

        uint16_t op_code = program->virtual_memory[entry_point + i] & 0x7F; // 0b01111111
        uint8_t rd = ((program->virtual_memory[entry_point + i] >> 7) | (program->virtual_memory[entry_point + i + 1] << 1)) & 0x1F;
        uint8_t funct3 = 0;
        uint8_t funct7 = 0;
        uint8_t rs1;
        uint8_t rs2;
        switch (op_code) {
            case R_TYPE:
                funct3 = (program->virtual_memory[entry_point + i + 1] >> 5) & 0x07;
                rs1 = ((program->virtual_memory[entry_point + i + 1] >> 7) | (program->virtual_memory[entry_point + i + 2] << 1)) & 0x1F; // 0x1F = 0b00011111
                rs2 = (program->virtual_memory[entry_point + i + 2] >> 4) & 0x1F; // 0x1F = 0b00011111
                funct7 = ((program->virtual_memory[entry_point + i + 2] >> 7) | (program->virtual_memory[entry_point + i + 3] << 1)) & 0x7F; // 0x7F = 0b01111111
                printf("R Type Instruct %d\n", funct3);
                break;
            case I_TYPE:
            case OPCODE_LW:
                funct3 = (program->virtual_memory[entry_point + i + 1] >> 5) & 0x07;
                rs1 = ((program->virtual_memory[entry_point + i + 1] >> 7) | (program->virtual_memory[entry_point + i + 2] << 1)) & 0x1F; // 0x1F = 0b00011111
                rs2 = ((program->virtual_memory[entry_point + i + 2] >> 4) | (program->virtual_memory[entry_point + i + 3] << 4)) & 0xFFF; // 0xFFF = 0b111111111111
                call_instruction(I_TYPE, combine(funct3, funct7), rd, rs1, (int8_t)rs2);
                break;
            case OPCODE_SW:
                funct3 = (program->virtual_memory[entry_point + i + 1] >> 5) & 0x07;
                rs1 = ((program->virtual_memory[entry_point + i + 1] >> 7) | (program->virtual_memory[entry_point + i + 2] << 1)) & 0x1F; // 0x1F = 0b00011111
                rs2 = (program->virtual_memory[entry_point + i + 2] >> 4) & 0x1F; // 0x1F = 0b00011111
                rd = (program->virtual_memory[entry_point + i + 1] >> 2) & 0x1F;;
                funct7 = program->virtual_memory[entry_point + i + 3] & 0x7F;
                uint8_t imm_4_0 = (program->virtual_memory[entry_point + i + 1] >> 2) & 0x1F;
                uint8_t imm_11_5 = program->virtual_memory[entry_point + i + 3] & 0xFE; // 0xFE = 0b11111110

                int16_t imm = (imm_11_5 << 5) | imm_4_0;
                if (imm & 0x400) { // Check if the sign bit (bit 11) is set
                    imm |= 0xF800; // Extend the sign to 16 bits
                }
                
                call_instruction(S_TYPE, combine(1, S_TYPE), rs1, rs2, imm);
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
    run_program(program);
    return 0;
}
