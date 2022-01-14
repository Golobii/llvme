#if !defined(CPU_H)
#define CPU_H

#include <iostream>
#include "memory.h"
#include "instructions.h"

#define NUM_OF_REG 8

class CPU
{
private:
    Memory mem;

    int ip;
    int acc;

    int registers[NUM_OF_REG];

    void execute(size_t instruction);

    int fetch();

    void step();

    void setReg(size_t reg, int value);

    int getReg(size_t reg);

public:
    CPU(Memory mem);
    ~CPU();

    void boot();
};

#endif // CPU_H
