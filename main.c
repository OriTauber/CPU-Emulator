
#include <stdio.h>

#include "assembler.h"
#include "cpu.h"



int main(void) {
    CPU cpu = {0};
    reset(&cpu);
    assemble(&cpu, "projects/fibonacci.asm");

    while (cpu.running) {
        step(&cpu);
    }

}
