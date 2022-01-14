#if !defined(MEMORY_H)
#define MEMORY_H

#include <cstddef>
#include <iostream>

typedef unsigned char Byte;

class Memory
{
private:
    Byte *mem;

public:
    Memory();
    ~Memory();

    size_t MAX_MEM = 0xffff;

    // change to unsinged int
    Byte getByte(size_t addr);
    void setByte(size_t addr, Byte value);
};

#endif // MEMORY_H
