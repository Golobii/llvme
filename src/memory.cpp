#include "../include/memory.h"

Byte Memory::getByte(unsigned int addr)
{
    return mem[addr];
}

void Memory::setByte(unsigned int addr, Byte value)
{
    mem[addr] = value;
}

Memory::Memory()
{
    mem = new Byte[MAX_MEM];
}

Memory::~Memory()
{
}
