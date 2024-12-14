#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <elf.h>
#include <CPU.h>

CPU* interpreter;

void load_elf(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open ELF file");
        exit(1);
    }

    // Read ELF header
    Elf64_Ehdr elf_header;
    if (fread(&elf_header, 1, sizeof(Elf64_Ehdr), file) != sizeof(Elf64_Ehdr)) {
        perror("Failed to read ELF header");
        exit(1);
    }

    // Check ELF magic number
    if (memcmp(elf_header.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "Not a valid ELF file\n");
        exit(1);
    }

    // Verify it is a 64-bit RISC-V ELF
    if (elf_header.e_machine != EM_RISCV || elf_header.e_ident[EI_CLASS] != ELFCLASS64) {
        fprintf(stderr, "Unsupported ELF type\n");
        exit(1);
    }

    // Iterate through program headers
    fseek(file, elf_header.e_phoff, SEEK_SET);
    for (int i = 0; i < elf_header.e_phnum; i++) {
        Elf64_Phdr phdr;
        if (fread(&phdr, 1, sizeof(Elf64_Phdr), file) != sizeof(Elf64_Phdr)) {
            perror("Failed to read program header");
            exit(1);
        }

        // Load segments of type PT_LOAD into memory
        if (phdr.p_type == PT_LOAD) {
            fseek(file, phdr.p_offset, SEEK_SET);
            fread(interpreter->memory + phdr.p_vaddr, 1, phdr.p_filesz, file);

            // Zero out the uninitialized portion in memory for bss
            if (phdr.p_memsz > phdr.p_filesz) {
                memset(interpreter->memory + phdr.p_vaddr + phdr.p_filesz, 0,
                       phdr.p_memsz - phdr.p_filesz);
            }
        }
    }

    // Set the CPU entry point
    interpreter->registers[PROGRAM_COUNTER] = elf_header.e_entry;

    fclose(file);
}

void print_binary(uint8_t byte) {
    for (int i = 7; i >= 0; i--) { // Loop from the most significant bit (MSB) to the least significant bit (LSB)
        printf("%c", (byte & (1 << i)) ? '1' : '0');
    }
}

// Function to simulate running the loaded ELF
void run_program() {
    uint64_t entry_point = interpreter->registers[PROGRAM_COUNTER];

    for(int i = 0; i< 100; i += 4){
        print_binary(interpreter->memory[entry_point + i+3]);
        print_binary(interpreter->memory[entry_point + i+2]);
        print_binary(interpreter->memory[entry_point + i+1]);
        print_binary(interpreter->memory[entry_point + i]);
        printf("\n");
    }
}

int main() {
    // Load ELF file into memory
    interpreter = initilize_CPU();
    
    load_elf("bin/EXEC.elf");

    // Execute the loaded program
    run_program();

    return 0;
}

/*
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
*/