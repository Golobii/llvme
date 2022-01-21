#if !defined(CPU_H)
#define CPU_H

#include <iostream>
#include "mapper.h"
#include "instructions.h"

#define NUM_OF_REG 8

class CPU
{
private:
    Mapper mem;

    int ip;
    int acc;

    unsigned int registers[NUM_OF_REG];

    // Zero Flag
    bool ZF;
    // Negative Flag
    bool NF;

    void execute(Byte instruction);

    void setFlagsForAcc();

    void setFlagsForAcc(int x);

    int fetch();

    void step();

    void setReg(unsigned int reg, int value);

    int getReg(unsigned int reg);

public:
    CPU(Mapper mem);
    ~CPU();

    void boot();
};

#endif // CPU_H
