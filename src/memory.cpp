#include "../include/memory.h"

Byte Memory::getByte(size_t addr)
{
    return mem[addr];
}

void Memory::setByte(size_t addr, Byte value)
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
