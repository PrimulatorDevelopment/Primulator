.section .text
.global _start

_start:
    # Set up the stack pointer (adjust stack size as needed)
    la sp, _stack_top

    # Call main
    call main

    # Exit with the return value of main
    mv a0, a0  # Return code from main in a0
    li a7, 93  # syscall exit
    ecall

    .section .bss
    .align 12
_stack_top:
    .space 4096  # Stack size (adjust as needed)