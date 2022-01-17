#if !defined(MEMORY_H)
#define MEMORY_H

typedef unsigned char Byte;

class Memory
{
private:
    Byte *mem;

public:
    Memory();
    ~Memory();

    unsigned int MAX_MEM = 0xffff;

    // change to unsinged int
    Byte getByte(unsigned int addr);
    void setByte(unsigned int addr, Byte value);
};

#endif // MEMORY_H
