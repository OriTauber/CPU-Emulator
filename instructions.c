//
// Created by User on 9/14/2026.
//

#include "instructions.h"

#include <stdio.h>

void SET(CPU *cpu, int reg, uint16_t val) {
    cpu->registers[reg] = val;
}

void ADD(CPU *cpu, uint8_t reg, uint8_t reg2) {
    uint16_t val1 = cpu->registers[reg];
    uint16_t val2 = cpu->registers[reg2];
    if ((uint32_t) val1 + val2 > 65535) {
        cpu->flags |= FLAG_CF;
    }
    else {
        cpu->flags &= ~FLAG_CF;
    }
    cpu->registers[reg] += val2;

}

void SUBTRACT(CPU *cpu, uint8_t reg, uint8_t reg2) {
    uint16_t val1 = cpu->registers[reg];
    uint16_t val2 = cpu->registers[reg2];
    if (val2 < val1) {
        cpu->flags |= FLAG_CF;
    }
    else {
        cpu->flags &= ~FLAG_CF;
    }
    cpu->registers[reg] -= val2;
}

void LOAD(CPU *cpu, int reg, uint16_t address) {
    if (address + 1 < MEMORY_SIZE) {
        uint16_t val = cpu->memory[address] | (cpu->memory[address + 1] << 8);
        cpu->registers[reg] = val;
    }
}

void STORE(CPU *cpu, uint16_t address, uint16_t val) {
    if (address < UINT16_MAX) {
        uint8_t lower = val;
        uint8_t higher = val >> 8;
        cpu->memory[address] = lower;
        cpu->memory[address + 1] = higher;
    }
}
void PRINT(CPU *cpu, uint8_t regAddr) {
    printf("Register %d value: %d\n", regAddr, cpu->registers[regAddr]);
}
