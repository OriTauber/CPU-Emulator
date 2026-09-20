//
// Created by User on 9/14/2026.
//

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "cpu.h"

void SET(CPU *cpu, int reg, uint16_t val);
void ADD(CPU *cpu, uint8_t reg, uint8_t reg2);
void SUBTRACT(CPU *cpu, uint8_t reg, uint8_t reg2);
void LOAD(CPU *cpu, int reg, uint16_t address);
void STORE(CPU *cpu, uint16_t address, uint16_t val);
void PRINT(CPU *cpu, uint8_t regAddr);
typedef void (*InstructionHandler)(CPU *cpu);
#endif //INSTRUCTIONS_H
