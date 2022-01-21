#include "../include/mapper.h"

Mapper::Mapper()
{
    mappedDevices = new MappedDevice[maxDevices];
}

Mapper::~Mapper()
{
}

unsigned int Mapper::findDevice(unsigned int addr)
{
    struct MappedDevice md;
    for (unsigned int i = 0; i < current; i++)
    {
        md = mappedDevices[i];
        if (md.startAddr <= addr && md.endAddr >= addr)
            return i;
    }

    // TODO: throw
    std::cout << "This mem addr isn't assigned to any device\n";
    exit(1);
    return 0;
}

void Mapper::map(Base *device, unsigned int startAddr, unsigned int endAddr)
{
    struct MappedDevice md;

    md.startAddr = startAddr;
    md.endAddr = endAddr;
    md.device = device;

    mappedDevices[current++] = md;
}

void Mapper::setByte(unsigned int addr, Byte value)
{
    unsigned int i = findDevice(addr);

    mappedDevices[i].device->setByte(addr - mappedDevices[i].startAddr, value);
}

Byte Mapper::getByte(unsigned int addr)
{
    unsigned int i = findDevice(addr);

    return mappedDevices[i].device->getByte(addr - mappedDevices[i].startAddr);
}