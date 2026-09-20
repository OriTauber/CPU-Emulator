#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define MEMORY_SIZE 65536

#define FLAG_ZF 0x01
#define FLAG_CF 0x02

typedef struct {
    uint16_t registers[8];
    uint16_t pc;
    uint16_t sp; //didn't implement stack yet
    uint8_t memory[MEMORY_SIZE];
    uint8_t flags;
    char running;
} CPU;

void reset(CPU *cpu);
uint8_t fetch8(CPU *cpu);
uint16_t fetch16(CPU *cpu);
void step(CPU *cpu);
void printState(CPU *cpu);
void printMemory(CPU *cpu, int bottom, int top);
void printFlags(CPU *cpu);

#endif