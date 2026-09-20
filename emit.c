//
// Created by User on 9/14/2026.
//

#include "emit.h"

void emitSET(CPU *cpu, uint8_t reg, uint16_t value, uint16_t startIndex) {
    if (startIndex + 3 >= MEMORY_SIZE) {
        return;
    }
    cpu->memory[startIndex] = 0x01;
    cpu->memory[startIndex + 1] = reg;
    cpu->memory[startIndex + 2] = (uint8_t) value;
    cpu->memory[startIndex + 3] = (uint8_t) (value >> 8);
}
void emitSTORE(CPU *cpu, uint8_t reg, uint16_t value, uint16_t startIndex) {
    if (startIndex + 3 >= MEMORY_SIZE) {
        return;
    }
    cpu->memory[startIndex] = 0x05;
    cpu->memory[startIndex + 1] = reg;
    cpu->memory[startIndex + 2] = (uint8_t) value;
    cpu->memory[startIndex + 3] = (uint8_t) (value >> 8);
}
void emitCMP(CPU *cpu, uint8_t reg, uint8_t reg2, uint16_t startIndex) {
    if (startIndex + 2 >= MEMORY_SIZE) {
        return;
    }
    cpu->memory[startIndex] = 0x06;
    cpu->memory[startIndex + 1] = reg;
    cpu->memory[startIndex + 2] = reg2;

}
void emitJE(CPU *cpu, uint16_t jumpAddr, uint16_t startIndex, char notMode) {
    if (startIndex + 2 >= MEMORY_SIZE) {
        return;
    }
    cpu->memory[startIndex] = notMode ? 0x08 : 0x07;
    cpu->memory[startIndex + 1] = (uint8_t) jumpAddr;
    cpu->memory[startIndex + 2] = (uint8_t) (jumpAddr >> 8);

}
void emitPRINT(CPU *cpu, uint8_t regAddr, uint16_t startIndex) {
    if (startIndex + 1 >= MEMORY_SIZE) {
        return;
    }
    cpu->memory[startIndex] = 0x0b;
    cpu->memory[startIndex + 1] = regAddr;


}

void emitADD(CPU *cpu, uint8_t reg, uint8_t reg2, uint16_t startIndex) {
    if (startIndex + 3 >= MEMORY_SIZE) {
        return;
    }
    cpu->memory[startIndex] = 0x02;
    cpu->memory[startIndex + 1] = reg;
    cpu->memory[startIndex + 2] = reg2;

}
void emitLOAD(CPU *cpu, uint8_t reg, uint16_t value, uint16_t startIndex) {
    if (startIndex + 3 >= MEMORY_SIZE) {
        return;
    }
    cpu->memory[startIndex] = 0x04;
    cpu->memory[startIndex + 1] = reg;
    cpu->memory[startIndex + 2] = (uint8_t) value;
    cpu->memory[startIndex + 3] = (uint8_t) (value >> 8);
}
void emitSUBTRACT(CPU *cpu, uint8_t reg, uint8_t reg2, uint16_t startIndex) {
    if (startIndex + 3 >= MEMORY_SIZE) {
        return;
    }
    cpu->memory[startIndex] = 0x03;
    cpu->memory[startIndex + 1] = reg;
    cpu->memory[startIndex + 2] = reg2;
}