#include "../../include/devices/base.h"

Base::Base()
{
    mem = new Byte[0xffff];
}

Base::~Base()
{
}

void Base::setByte(unsigned int addr, Byte value)
{
}

Byte Base::getByte(unsigned int addr)
{
    return 0;
}
