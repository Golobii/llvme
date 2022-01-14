class Base
{
private:
public:
    virtual int getByte() = 0;
};

class Ram : public Base
{
private:
public:
    int getByte()
    {
        return 0;
    }
};

class Screen : public Base
{
private:
public:
    int getByte()
    {
        return 1;
    }
};

int main(int argc, char const *argv[])
{
    Ram ram;
    Screen scr;

    Base arr[2] = {ram, scr};

    return 0;
}
