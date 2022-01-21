#if !defined(SCREEN_H)
#define SCREEN_H

#include <iostream>
#include <ncurses.h>

#include "base.h"

class Screen : public Base
{
private:
public:
    Screen();
    ~Screen();

    virtual void setByte(unsigned int addr, Byte value);
    virtual Byte getByte(unsigned int addr);
};

#endif // SCREEN_H
