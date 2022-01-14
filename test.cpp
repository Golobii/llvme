#include <iostream>

class Device
{
private:
public:
    Device();
    virtual ~Device();

    virtual int getByte(int addr) = 0;
    virtual void setByte(int addr, int val){};
};

Device::Device()
{
}

Device::~Device()
{
}

class Screen : public Device
{
private:
public:
    Screen();
    ~Screen();

    virtual int getByte(int addr);
    virtual void setByte(int addr, int val);
};

Screen::Screen()
{
}

Screen::~Screen()
{
}

void Screen::setByte(int addr, int val)
{
}

int Screen::getByte(int addr)
{
    return 69;
}

void test(Device *dev)
{
    std::cout << dev->getByte(3) << '\n';
}

int main(int argc, char const *argv[])
{
    Screen scr;
    test(&scr);
    return 0;
}
