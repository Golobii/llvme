#include "../include/cpu.h"

CPU::CPU(Mapper mem)
{
    this->mem = mem;
}

void CPU::boot()
{
    ip = acc = 0;
    ZF = NF = false;

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

void CPU::setFlagsForAcc()
{
    NF = acc < 0;
    ZF = acc == 0;
}

void CPU::setFlagsForAcc(int x)
{
    NF = x < 0;
    ZF = x == 0;
}

void CPU::execute(Byte instruction)
{
    unsigned int reg;
    unsigned int val;
    unsigned int val2;
    switch (instruction)
    {
    case DEBUG:
        for (unsigned int i = 0; i < NUM_OF_REG; i++)
        {
            std::cout << "Reg" << i + 1 << ": " << getReg(i) << "\n";
        }

        printf("Acc: %d\n", acc);
        printf("Ip: %d\n", ip);
        printf("ZF: %d\n", ZF);
        printf("NF: %d\n", NF);
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
        setFlagsForAcc();
        break;

    case JMP:
        ip = fetch();
        break;

    case ADD:
        acc += getReg(fetch());
        setFlagsForAcc();
        break;

    case SUB:
        acc -= getReg(fetch());
        setFlagsForAcc();
        break;

    case INCA:
        acc++;
        setFlagsForAcc();
        break;

    case CLA:
        acc = 0;
        ZF = true;
        NF = false;
        break;

    case LDR:
        val = fetch();
        reg = fetch();
        setReg(reg, mem.getByte(val));
        break;

    case STR:
        mem.setByte(fetch(), getReg(fetch()));
        break;

    case LLR:
        setReg(fetch(), fetch());
        break;

    case CMP:
        setFlagsForAcc(getReg(fetch()) - getReg(fetch()));
        break;

    case JNE:
        if (!ZF)
        {
            ip = fetch();
        }
        else
        {
            ip++;
        }
        break;

    case INCR:
        reg = fetch();
        setReg(reg, getReg(reg) + 1);
        break;

    case AND:
        acc &= getReg(fetch());
        setFlagsForAcc();
        break;

    case OR:
        acc |= getReg(fetch());
        setFlagsForAcc();
        break;

    case XOR:
        acc ^= acc;
        setFlagsForAcc();
        break;

    case NOT:
        acc = ~acc;
        setFlagsForAcc();
        break;

    case SB:
        val = fetch();
        val2 = fetch();
        mem.setByte(val, val2);
        break;

    case NOOP:
        break;

    case HLT:
        return;

    default:
        std::cout << "System error\n";
        std::cout << "Unknown instruction: " << instruction << " \n";
        return;
    }

    step();
}

int CPU::getReg(unsigned int reg)
{
    if (reg > NUM_OF_REG)
    {
        throw std::overflow_error("Register index out of range");
    }

    return registers[reg];
}

void CPU::setReg(unsigned int reg, int value)
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
