//
// Created by User on 9/14/2026.
//

#include "assembler.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "emit.h"
#define MAX_PATH_SIZE 1024
#define MAX_LABELS 256
#define MAX_LABEL_NAME 64
typedef enum {
    OPERAND_NONE,
    OPERAND_REG,
    OPERAND_IMM16,
    OPERAND_ADDR16,
    OPERAND_LABEL
} OperandType;
typedef struct {
    const char *name;
    uint8_t opcode;

    OperandType arg1Type;
    OperandType arg2Type;
} InstructionDef;
typedef struct {
    char name[MAX_LABEL_NAME];
    uint16_t address;
} LabelDef;
LabelDef labels[MAX_LABELS] = {};
int labelCount = 0;
InstructionDef instructions[] = {
    {"NOP",   0x00, OPERAND_NONE,  OPERAND_NONE},
    {"SET",   0x01, OPERAND_REG,  OPERAND_IMM16},
    {"ADD",   0x02, OPERAND_REG,  OPERAND_REG},
    {"SUBTRACT", 0x03, OPERAND_REG,  OPERAND_REG},
    {"LOAD",  0x04, OPERAND_REG,  OPERAND_ADDR16},
    {"STORE", 0x05, OPERAND_REG,  OPERAND_ADDR16},
    {"CMP",   0x06, OPERAND_REG,  OPERAND_REG},
    {"JE",    0x07, OPERAND_LABEL, OPERAND_NONE},
    {"JNE",    0x08, OPERAND_LABEL, OPERAND_NONE},
    {"PRINT", 0x0b, OPERAND_REG, OPERAND_NONE},
    {"HALT",  0xFF, OPERAND_NONE, OPERAND_NONE}
    ,
};

InstructionDef *findInstruction(char *name) {
    int count = sizeof(instructions) / sizeof(instructions[0]);

    for (int i = 0; i < count; i++) {
        if (strcmp(name, instructions[i].name) == 0) {
            return &instructions[i];
        }
    }

    return NULL;
}
long parseNumber(char *arg) {
    char *end;
    long value = strtol(arg, &end, 0);
    return value;
}
long parseLabel(char *arg) {

    for (int i = 0; i < labelCount; i++) {
        if (strcmp(arg, labels[i].name) == 0) {
            return labels[i].address;
        }
    }
    printf("Unknown label: %s\n", arg);
    return -1;
}
long parseReg(char *arg) {
    char *end;
    long value = strtol(arg + 1, &end, 0);
    return value;
}
long parseOperand(char *arg, OperandType type) {
    switch (type) {
        case OPERAND_REG:
            return parseReg(arg);

        case OPERAND_IMM16:
            return parseNumber(arg);

        case OPERAND_ADDR16:
            return parseNumber(arg);
        case OPERAND_LABEL:
            return parseLabel(arg);
        case OPERAND_NONE:
            return 0;
    }

    return -1;
}
bool ends_with(const char *str, char ch) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);

    // Check if the string is empty, then check the last character
    return (len > 0) && (str[len - 1] == ch);
}


int updateLabel(char *opcode, uint16_t memoryIndex) {
    if (ends_with(opcode, ':')) {
        opcode[strlen(opcode) - 1] = '\0';
        strcpy(labels[labelCount].name, opcode);
        labels[labelCount++].address = memoryIndex;
        return 1;
    }
    return 0;
}
bool isLabelDefined(char *opcode) {
    opcode[strlen(opcode) - 1] = '\0';
    for (int i = 0; i < labelCount; i++) {
        if (strcmp(opcode, labels[i].name) == 0) {
            return true;
        }
    }
    return false;
}
int updateLabelsPass(FILE *file) {

    char line[256];
    uint16_t memoryIndex = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char *opcode = strtok(line, ", \n");
        if (opcode == NULL) {
            continue;
        }
        if (updateLabel(opcode, memoryIndex)) {
            continue;
        }
        InstructionDef *instruction = findInstruction(opcode);
        if (instruction == NULL) {
            continue;
        }



        switch (instruction->opcode) {
            case 0x00:
                memoryIndex += 1;
                break;
            case 0x01:

                memoryIndex+=4;
                break;
            case 0x02:

                memoryIndex+=3;
                break;
            case 0x03:

                memoryIndex+=3;
                break;
            case 0x04:

                memoryIndex+=4;
                break;
            case 0x05:

                memoryIndex+=4;
                break;
            case 0x06:
                memoryIndex+=3;
                break;
            case 0x07:

                memoryIndex+=3;
                break;
            case 0x08:

                memoryIndex+=3;
                break;
            case 0x0b:
                memoryIndex+=2;
                break;
            case 0xff:
                memoryIndex+=1;
                break;
            default:
                printf("unknown opcode");
        }

    }
    rewind(file);
    return 0;
}



int assemble(CPU *cpu, const char *filename) {

    char filepath[MAX_PATH_SIZE];

    snprintf(filepath, sizeof(filepath), "../%s", filename);
    FILE *file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }
    updateLabelsPass(file);
    char line[256];
    uint16_t memoryIndex = 0;


    while (fgets(line, sizeof(line), file) != NULL) {
        char *opcode = strtok(line, ", \n");
        if (opcode == NULL) {
            continue;
        }
        char *arg1 = strtok(NULL, ", \n");
        char *arg2 = strtok(NULL, ", \n");

        InstructionDef *instruction = findInstruction(opcode);
        if (instruction == NULL) {
            if (!isLabelDefined(opcode)) {
                printf("Unknown instruction: %s\n", opcode);
            }
            continue;
        }

        long binOP = instruction->opcode;

        long binARG1 = 0;
        long binARG2 = 0;

        if (arg1 != NULL)
            binARG1 = parseOperand(arg1, instruction->arg1Type);

        if (arg2 != NULL)
            binARG2 = parseOperand(arg2, instruction->arg2Type);


        switch (binOP) {
            case 0x00:
                cpu->memory[memoryIndex] = 0x00;
                memoryIndex += 1;
                break;
            case 0x01:
                emitSET(cpu, binARG1, binARG2, memoryIndex);
                memoryIndex+=4;
                break;
            case 0x02:
                emitADD(cpu, binARG1, binARG2, memoryIndex);
                memoryIndex+=3;
                break;
            case 0x03:
                emitSUBTRACT(cpu, binARG1, binARG2, memoryIndex);
                memoryIndex+=3;
                break;
            case 0x04:
                emitLOAD(cpu, binARG1, binARG2, memoryIndex);
                memoryIndex+=4;
                break;
            case 0x05:
                emitSTORE(cpu, binARG1, binARG2, memoryIndex);
                memoryIndex+=4;
                break;
            case 0x06:
                emitCMP(cpu, binARG1, binARG2, memoryIndex);
                memoryIndex+=3;
                break;
            case 0x07:
                if (binARG1 == -1) {
                    break;
                }
                emitJE(cpu, binARG1, memoryIndex, 0);
                memoryIndex+=3;
                break;
            case 0x08:
                if (binARG1 == -1) {
                    break;
                }
                emitJE(cpu, binARG1, memoryIndex, 1);
                memoryIndex+=3;
                break;
            case 0x0b:
                emitPRINT(cpu, binARG1, memoryIndex);
                memoryIndex+=2;
                break;
            case 0xff:
                cpu->memory[memoryIndex] = 0xff;
                memoryIndex+=1;
                break;
            default:
                printf("unknown opcode");
        }

        //printf("Instruction: %s, Arg1: %s, Arg2: %s\n", opcode, arg1, arg2);

    }
    fclose(file);
    return 0;
}
