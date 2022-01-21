#include "../../include/devices/screen.h"

Byte Screen::getByte(unsigned int addr)
{
    return 0;
}

void Screen::setByte(unsigned int addr, Byte value)
{
    std::cout << (int)value << '\n';
    mvprintw(0, 0, "x");
    getch();
}

Screen::Screen()
{
    initscr();
}

Screen::~Screen()
{
}