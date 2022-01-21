#include <iostream>
#include <fstream>
#include <vector>

#include "../include/cpu.h"
#include "../include/mapper.h"

#include "../include/devices/ram.h"
#include "../include/devices/screen.h"

void flashMem(std::string fileName, Mapper *mem)
{
    std::ifstream f;
    f.open(fileName, std::ios::binary);

    if (!f.is_open())
        throw std::runtime_error("Error: file not found");

    std::vector<char> bytes(
        (std::istreambuf_iterator<char>(f)),
        (std::istreambuf_iterator<char>()));

    for (size_t i = 0; i < bytes.size(); i++)
    {
        Byte byt = bytes.at(i);
        mem->setByte(i, byt);
    }

    f.close();
}

int main(int argc, char const *argv[])
{
    Mapper mm;
    Ram ram;
    Screen scr;

    mm.map(&ram, 0x00, 0xf0);
    mm.map(&scr, 0xf1, 0xfa);

    flashMem(argv[1], &mm);

    CPU cpu(mm);

    cpu.boot();

    return 0;
}
