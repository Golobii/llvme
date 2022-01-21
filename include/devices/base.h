#if !defined(BASE_H)
#define BASE_H

typedef unsigned char Byte;

class Base
{
private:
    Byte *mem;

public:
    Base();
    virtual ~Base();

    virtual void setByte(unsigned int addr, Byte value);
    virtual Byte getByte(unsigned int addr);
};

#endif // BASE_H
