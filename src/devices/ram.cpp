#include "../../include/devices/ram.h"

Ram::Ram()
{
    mem = new Byte[0xffff];
}

Ram::~Ram()
{
}

void Ram::setByte(unsigned int addr, Byte value)
{
    mem[addr] = value;
}

Byte Ram::getByte(unsigned int addr)
{
    return mem[addr];
}
