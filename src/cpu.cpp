#include "../include/cpu.h"

CPU::CPU(Memory mem)
{
    this->mem = mem;
}

void CPU::boot()
{
    ip = acc = 0;
    for (size_t i = 0; i < NUM_OF_REG; i++)
    {
        setReg(i, 0);
    }

    step();
}

int CPU::fetch()
{
    int data = mem.getByte(ip++);
    return data;
}

void CPU::execute(size_t instruction)
{
    int reg;
    int val;
    switch (instruction)
    {
    case DEBUG:
        for (size_t i = 0; i < NUM_OF_REG; i++)
        {
            std::cout << "Reg" << i << ": " << getReg(i) << "\n";
        }

        printf("Acc: %d\n", acc);
        printf("Ip: %d\n", ip);
        getchar();

        break;

    case LDAC:
        acc = mem.getByte(fetch());
        break;

    case STAC:
        mem.setByte(fetch(), acc);
        break;

    case MVAC:
        setReg(fetch(), acc);
        break;

    case MVR:
        acc = getReg(fetch());
        break;

    case JMP:
        ip = fetch();
        break;

    case ADD:
        acc += getReg(fetch());
        break;

    case SUB:
        acc -= getReg(fetch());
        break;

    case INCA:
        acc++;
        break;

    case CLA:
        acc = 0;
        break;

    case LDR:
        setReg(fetch(), mem.getByte(fetch()));
        break;

    case STR:
        mem.setByte(fetch(), getReg(fetch()));
        break;

    case LLR:
        setReg(fetch(), fetch());
        break;

    case AND:
        acc &= getReg(fetch());
        break;

    case OR:
        acc |= getReg(fetch());
        break;

    case XOR:
        acc ^= acc;
        break;

    case NOT:
        acc = ~acc;
        break;

    case HLT:
        return;

    default:
        break;
    }

    step();
}

int CPU::getReg(size_t reg)
{
    if (reg > NUM_OF_REG)
    {
        throw std::overflow_error("Register index out of range");
    }

    return registers[reg];
}

void CPU::setReg(size_t reg, int value)
{
    if (reg > NUM_OF_REG)
    {
        throw std::overflow_error("Register index out of range");
    }
    registers[reg] = value;
}

void CPU::step()
{
    execute(fetch());
}

CPU::~CPU()
{
}
