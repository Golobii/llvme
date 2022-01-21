#if !defined(MAPPER_H)
#define MAPPER_H

#include <iostream>
#include <stdlib.h>

#include "devices/base.h"

struct MappedDevice
{
    Base *device;
    unsigned int startAddr;
    unsigned int endAddr;
};

class Mapper
{
private:
    unsigned char current = 0;
    struct MappedDevice *mappedDevices;

    unsigned int findDevice(unsigned int addr);

public:
    Mapper();
    ~Mapper();

    unsigned int maxDevices = 10;

    void map(Base *device, unsigned int startAddr, unsigned int endAddr);

    void setByte(unsigned int addr, Byte value);
    Byte getByte(unsigned int addr);
};

#endif // MAPPER_H
