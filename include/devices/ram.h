#if !defined(RAM_H)
#define RAM_H

#include "base.h"

class Ram : public Base
{
private:
    Byte *mem;

public:
    Ram();
    ~Ram();

    virtual void setByte(unsigned int addr, Byte value);
    virtual Byte getByte(unsigned int addr);
};

#endif // RAM_H
