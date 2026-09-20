//
// Created by User on 9/14/2026.
//

#include "decoder.h"

#include <stdio.h>

#include "instructions.h"

void decode(CPU *cpu, uint8_t opcode) {
    switch (opcode) {
        //NOP
        case 0x00: {
            break;
        }
        case 0x01: {
            // SET
            uint8_t reg = fetch8(cpu);
            uint16_t val = fetch16(cpu);

            SET(cpu, reg, val);
            break;
        }

        case 0x02: {
            // ADD
            uint8_t reg = fetch8(cpu);
            uint8_t reg2 = fetch8(cpu);

            ADD(cpu, reg, reg2);
            break;
        }

        case 0x03: {
            // SUBTRACT
            uint8_t reg = fetch8(cpu);
            uint8_t reg2 = fetch16(cpu);

            SUBTRACT(cpu, reg, reg2);
            break;
        }

        case 0x04: {
            // LOAD
            uint8_t reg = fetch8(cpu);
            uint16_t address = fetch16(cpu);

            LOAD(cpu, reg, address);
            break;
        }

        case 0x05: {
            // STORE
            uint8_t reg = fetch8(cpu);
            uint16_t address = fetch16(cpu);

            STORE(cpu, address, cpu->registers[reg]);
            break;
        }
        case 0x06: {
            //CMP
            uint8_t firstReg = fetch8(cpu);
            uint8_t secReg = fetch8(cpu);

            if (cpu->registers[firstReg] == cpu->registers[secReg]) {
                cpu->flags |= FLAG_ZF;
            }
            else {
                cpu->flags &= ~FLAG_ZF;
            }
            break;
        }
        case 0x07: {
            //JE
            uint16_t jumpAddress = fetch16(cpu);
            if (cpu->flags & FLAG_ZF) {
                cpu->pc = jumpAddress;
            }
            break;
        }
        case 0x08: {
            //JNE
            uint16_t jumpAddress = fetch16(cpu);
            if (!(cpu->flags & FLAG_ZF)) {
                cpu->pc = jumpAddress;
            }
            break;
        }

        case 0x0b: {
            //PRINT
            uint8_t printAddr = fetch8(cpu);
            PRINT(cpu, printAddr);
            break;
        }
        case 0xFF: {
            cpu->running = 0;
            break;
        }
        default: {
            printf("Invalid opcode: %02x at PC=%04x\n",
                   opcode, cpu->pc - 1);
            cpu->running = 0;
            break;
        }
    }
}
