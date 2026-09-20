//
// Created by User on 9/14/2026.
//

#ifndef HEREWEGO_EMIT_H
#define HEREWEGO_EMIT_H
#include "cpu.h"

void emitSET(CPU *cpu, uint8_t reg, uint16_t value, uint16_t startIndex);
void emitADD(CPU *cpu, uint8_t reg, uint8_t reg2, uint16_t startIndex);
void emitLOAD(CPU *cpu, uint8_t reg, uint16_t value, uint16_t startIndex);
void emitSUBTRACT(CPU *cpu, uint8_t reg, uint8_t reg2, uint16_t startIndex);
void emitSTORE(CPU *cpu, uint8_t reg, uint16_t value, uint16_t startIndex);
void emitCMP(CPU *cpu, uint8_t reg, uint8_t reg2, uint16_t startIndex);
void emitJE(CPU *cpu, uint16_t jumpAddr, uint16_t startIndex, char notMode);
void emitPRINT(CPU *cpu, uint8_t regAddr, uint16_t startIndex);
#endif //HEREWEGO_EMIT_H
