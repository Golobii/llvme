#include <iostream>
#include <fstream>
#include <vector>

#include "../include/memory.h"
#include "../include/cpu.h"

void flashMem(std::string fileName, Memory *mem)
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

    Memory mem;

    flashMem(argv[1], &mem);

    CPU cpu(mem);

    cpu.boot();

    return 0;
}
