#include <Executable.h>


Program* load_program(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open ELF file\n");
        exit(1);
    }

    Program* program = (Program*) malloc(sizeof(Program));
    program->virtual_memory = (uint8_t*)MAGIC_RAM;

    // Read ELF header
    if (fread(&program->elf_header, 1, sizeof(Elf64_Ehdr), file) != sizeof(Elf64_Ehdr)) {
        perror("Failed to read ELF header\n");
        fclose(file);
        free(program);
        exit(1);
    }

    // Check ELF magic number
    if (memcmp(program->elf_header.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "Not a valid ELF file\n");
        fclose(file);
        free(program);
        exit(1);
    }

    // Verify it is a 64-bit RISC-V ELF
    if (program->elf_header.e_machine != EM_RISCV || program->elf_header.e_ident[EI_CLASS] != ELFCLASS64) {
        fprintf(stderr, "Unsupported ELF type\n");
        fclose(file);
        free(program);
        exit(1);
    }


    // Iterate through program headers
    fseek(file, program->elf_header.e_phoff, SEEK_SET);
    for (int i = 0; i < program->elf_header.e_phnum; i++) {
        Elf64_Phdr phdr;
        if (fread(&phdr, 1, sizeof(Elf64_Phdr), file) != sizeof(Elf64_Phdr)) {
            perror("Failed to read program header\n");
            fclose(file);
            free(program);
            exit(1);
        }

        // Load segments of type PT_LOAD into memory
        if (phdr.p_type == PT_LOAD) {

            if (phdr.p_vaddr + phdr.p_memsz > MEM_SIZE)
            {
                perror("Not enough system memory\n");
                fclose(file);
                free(program);
                exit(1);
            }else if (program->virtual_memory == (uint8_t*)MAGIC_RAM)
                program->virtual_memory = calloc(phdr.p_vaddr + phdr.p_memsz + 0x128, sizeof(uint8_t));

            if (program->virtual_memory == (uint8_t*)MAGIC_RAM)
            {
                perror("A fatal error has occured\n");
                fclose(file);
                free(program);
                exit(1);
            }

            // Load the segment into memory
            fseek(file, phdr.p_offset, SEEK_SET);
            fread(program->virtual_memory + phdr.p_vaddr, 1, phdr.p_filesz, file);

            // Zero out the uninitialized portion in memory for bss
            if (phdr.p_memsz > phdr.p_filesz) {
                memset(program->virtual_memory + phdr.p_vaddr + phdr.p_filesz, 0,
                       phdr.p_memsz - phdr.p_filesz);
            }

            // Update highest_address to be the end of this segment
            uint64_t segment_end = phdr.p_vaddr + phdr.p_memsz;
            if (segment_end > program->min_address) {
                program->min_address = segment_end;
            }
        }
    }

    // Set the CPU entry point
    //interpreter->registers[PROGRAM_COUNTER] = elf_header.e_entry;

    fclose(file);
    return program;
}

void print_binary(uint8_t byte) {
    for (int i = 7; i >= 0; i--) { // Loop from the most significant bit (MSB) to the least significant bit (LSB)
        printf("%c", (byte & (1 << i)) ? '1' : '0');
    }
}

// Function to simulate running the loaded ELF
void run_program(CPU* interpreter, Program* program) {
    interpreter->registers[PROGRAM_COUNTER] = program->elf_header.e_entry;
    uint64_t entry_point = interpreter->registers[PROGRAM_COUNTER];

    for(int i = 0; i< 40; i += 4){
        print_binary(program->virtual_memory[entry_point + i+3]);
        print_binary(program->virtual_memory[entry_point + i+2]);
        print_binary(program->virtual_memory[entry_point + i+1]);
        print_binary(program->virtual_memory[entry_point + i]);
        printf("\n");
    }

    for(int i = program->min_address; i > 0 ; i--){
        //print_binary(interpreter->memory[i]);
        //printf("\n");
    }


}

