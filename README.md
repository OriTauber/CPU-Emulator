# Custom 16-bit CPU Emulator & Assembler

A small custom CPU emulator and assembler written in **C**.

The project implements a simple 16-bit CPU from scratch, including its memory, registers, flags, instruction set, CPU execution cycle, and an assembler that converts a custom assembly language into machine code.

The goal of the project is to understand how CPUs, machine code, assemblers, memory, and instruction execution work at a low level.

---

## Project Structure

The project consists of two main parts:

### CPU Emulator

The emulator simulates a custom 16-bit CPU.

It contains:

* 8 general-purpose 16-bit registers
* 16-bit Program Counter (`PC`)
* 16-bit Stack Pointer (`SP`)
* 64 KiB of memory
* CPU flags
* Instruction fetching and decoding
* Arithmetic and memory operations
* Conditional jumps

Memory addresses range from:

```text
0x0000 - 0xFFFF
```

### Assembler

The assembler converts human-readable assembly code such as:

```asm
SET R0, 1
SET R1, 5

loop:
ADD R0, R1
CMP R0, R1
JNE loop

HALT
```

into the machine-code representation understood by the CPU emulator.

The assembler supports labels and performs multiple passes so that forward-referenced labels can be resolved.

---

# CPU Architecture

## Registers

The CPU contains 8 general-purpose registers:

```text
R0 - R7
```

Each register is 16 bits wide.

For example:

```asm
SET R0, 10
ADD R0, R1
```

---

## Memory

The CPU has:

```text
65536 bytes
```

of memory (64 KiB).

Each memory address stores one byte.

```text
0x0000
   |
   v
   ...
   |
   v
0xFFFF
```

---

## Flags

The CPU currently supports:

### Zero Flag

```text
ZF = 0x01
```

Set when a comparison evaluates as equal.

### Carry Flag

```text
CF = 0x02
```

Used for arithmetic overflow/borrow detection.

---

# Instruction Set

| Instruction | Opcode | Operands      | Description                      |
| ----------- | -----: | ------------- | -------------------------------- |
| `NOP`       | `0x00` | —             | Does nothing                     |
| `SET`       | `0x01` | `REG, IMM16`  | Set a register to a value        |
| `ADD`       | `0x02` | `REG, REG`    | Add two registers                |
| `SUBTRACT`  | `0x03` | `REG, IMM16`  | Subtract an immediate value      |
| `LOAD`      | `0x04` | `REG, ADDR16` | Load a 16-bit value from memory  |
| `STORE`     | `0x05` | `REG, ADDR16` | Store a register value in memory |
| `CMP`       | `0x06` | `REG, REG`    | Compare two registers            |
| `JE`        | `0x07` | `LABEL`       | Jump if equal                    |
| `JNE`       | `0x08` | `LABEL`       | Jump if not equal                |
| `PRINT`     | `0x0B` | `REG`         | Print a register value           |
| `HALT`      | `0xFF` | —             | Stop execution                   |

---

# Assembly Syntax

## SET

Sets a register to a 16-bit value.

```asm
SET R0, 10
SET R1, 0xFF
```

---

## ADD

Adds one register to another.

```asm
ADD R0, R1
```

Equivalent to:

```text
R0 = R0 + R1
```

---

## SUBTRACT

Subtracts the second register from the first.

```asm
SUBTRACT R0, R2
```

---

## LOAD

Loads a 16-bit value from memory.

```asm
LOAD R0, 0x100
```

This reads the value stored at memory address `0x100` and places it into `R0`.

---

## STORE

Stores a register's value into memory.

```asm
STORE R0, 0x100
```

---

## CMP

Compares two registers and updates the Zero Flag.

```asm
CMP R0, R1
```

If:

```text
R0 == R1
```

then:

```text
ZF = 1
```

---

## JE

Jump if the Zero Flag is set.

```asm
JE end
```

---

## JNE

Jump if the Zero Flag is not set.

```asm
JNE loop
```

---

## PRINT

Prints the value of a register.

```asm
PRINT R0
```

---

## HALT

Stops the CPU.

```asm
HALT
```

---

# Labels

Labels can be used to create named jump targets.

```asm
loop:
    ADD R0, R1
    CMP R0, R1
    JNE loop

end:
    HALT
```

Labels are converted by the assembler into their corresponding memory addresses.

The assembler uses multiple passes:

1. **First pass** — determines instruction locations and records label addresses.
2. **Second pass** — generates the actual machine code and resolves labels.

This allows jumps to labels that appear later in the program.

---

# Example Program

The following program repeatedly adds `R1` to `R0` until the values become equal:

```asm
SET R0, 1
SET R1, 1

loop:
ADD R0, R1
CMP R0, R1
JNE loop

PRINT R0
HALT
```

---

# Machine Code

Each assembly instruction is converted into bytes in CPU memory.

For example:

```asm
SET R0, 0x1234
```

is encoded as:

```text
01 00 34 12
```

Where:

```text
01       opcode
00       register R0
34       low byte
12       high byte
```

The CPU uses **little-endian** encoding for 16-bit values.

---

# CPU Execution

The emulator follows a simple fetch/decode/execute cycle:

```text
        ┌─────────┐
        │  FETCH  │
        └────┬────┘
             ↓
        ┌─────────┐
        │ DECODE  │
        └────┬────┘
             ↓
        ┌─────────┐
        │ EXECUTE │
        └────┬────┘
             │
             └──────→ FETCH
```

The `PC` determines where the next instruction is fetched from.

For example:

```c
uint8_t opcode = fetch8(cpu);
decode(cpu, opcode);
```

---

# Building

Compile the project using your C compiler.

For example with GCC:

```bash
gcc *.c -o emulator
```

Run it with:

```bash
./emulator
```

On Windows:

```bash
emulator.exe
```

---

# Assembly Program

Assembly programs use the custom `.asm` format.

Example:

```text
program.asm
```

```asm
SET R0, 5
SET R1, 10
ADD R0, R1
PRINT R0
HALT
```

The assembler reads the file and places the resulting machine code into the CPU's memory.

---

# Project Goals

This project was built to explore low-level computer architecture concepts, including:

* CPU architecture
* Registers
* Memory
* Machine code
* Instruction encoding
* Fetch/decode/execute cycles
* Assembly languages
* Assemblers
* Labels
* Two-pass assembly
* Little-endian encoding
* CPU flags
* Instruction decoding
* C systems programming

The project is intentionally simple, making the relationship between assembly instructions and the underlying machine code easy to inspect.
