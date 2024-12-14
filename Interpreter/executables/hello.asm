main:
    addi    sp,sp,-32
    sd      ra,24(sp)
    sd      s0,16(sp)
    addi    s0,sp,32
    li      a5,4
    sw      a5,-20(s0)
    li      a5,0
    mv      a0,a5
    ld      ra,24(sp)
    ld      s0,16(sp)
    addi    sp,sp,32
    jr      ra

// int main() {
// int a = 3 + 1;
// }