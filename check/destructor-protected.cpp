#include <iostream>

class Base
{
public:

    virtual ~Base() {}
};

class A : public Base
{
public:

    A() :
        _mem(new int(6))
    {}

protected:

    ~A()
    {
        delete _mem;
        std::cout << "Destructor A" << std::endl;
    }

private:

    int* _mem;
};

int main()
{
    std::cout << "Before" << std::endl;
    {
        Base* base = new A;
        delete base;
        //A* a = new A;         This not works because the destructor is protected.
        //delete a;
    }
    std::cout << "After" << std::endl;

    return 0;
}