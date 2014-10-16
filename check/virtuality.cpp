/**
 * Book: Exceptional C++ Style
 * Item 18: Virtuality
 */

#include <iostream>

class Base
{
public:

    virtual ~Base() {}

    void execute()
    {
        executeVirtual();
    }

protected:

    virtual void executeBaseCode()
    {
        std::cout << "Executing Base code." << std::endl;
    }

private:

    virtual void executeVirtual() = 0;

};

class Derived : public Base
{
private:

    void executeVirtual()
    {
        executeBaseCode();
        std::cout << "Executing Derived code." << std::endl;
    }

};

int main()
{
    Base* b = new Derived;
    b->execute();
    delete b;

    return 0;
}
