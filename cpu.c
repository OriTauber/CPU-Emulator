#include <stdint.h>
#include <stdio.h>
#include "cpu.h"

#include "decoder.h"
#include "instructions.h"


void reset(CPU *cpu) {
    cpu->sp = 255;
    cpu->pc = 0;
    cpu->running = 1;
    cpu->flags = 0;
    for (int i = 0; i < 65536; i++) {
        cpu->memory[i] = 0;
    }
    for (int i = 0; i < 8; i++) {
        cpu->registers[i] = 0;
    }
}

void printState(CPU *cpu) {
    printf("Flags: %d\n", cpu->flags);
    printf("SP: %x\n", cpu->sp);
    printf("PC: %x\n", cpu->pc);
    for (int i = 0; i < 8; i++) {
        printf("Register %d: %x\n", i, cpu->registers[i]);
    }
}

void printMemory(CPU *cpu, int bottom, int top) {
    for (int i = bottom; i < top; i++) {
        printf("Memory %d: %x\n", i, cpu->memory[i]);
    }
}
void printFlags(CPU *cpu) {
    printf("Flags: %x\n", cpu->flags);
}
uint8_t fetch8(CPU *cpu) {
    return cpu->memory[cpu->pc++];
}

uint16_t fetch16(CPU *cpu) {
    uint16_t lower = cpu->memory[cpu->pc++];
    uint16_t higher = cpu->memory[cpu->pc++] << 8;
    return lower | higher;
}

void step(CPU *cpu) {

    uint8_t opc = fetch8(cpu);
    decode(cpu, opc);

}