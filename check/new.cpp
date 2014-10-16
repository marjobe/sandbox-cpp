#include <cstddef>
#include <iostream>

class FastMemory
{};

class Base
{
public:

    virtual void print() const = 0;

    static void* operator new(std::size_t s, const FastMemory&)
    {
        std::cout << "operator new(std::size_t s, const FastMemory&) called!" << std::endl;
        return ::operator new(s);
    }

    static void* operator new(std::size_t s) throw(std::bad_alloc)
    {
        std::cout << "operator new(std::size_t s) called!" << std::endl;
        return ::operator new(s);
    }

    static void* operator new(std::size_t s, const std::nothrow_t& n) throw()
    {
        std::cout << "operator new(std::size_t s, const std::nothrow_t& n) called!" << std::endl;
        return ::operator new(s, n);
    }

    static void* operator new(std::size_t s, void* p) throw()
    {
        std::cout << "operator new(std::size_t s, void* p) called!" << std::endl;
        return ::operator new(s, p);
    }

};

class Derived : public Base
{
public:

    Derived() :
        i(133)
    {}

    virtual void print() const
    {
        std::cout << i << std::endl;
    }

private:

    int i;
};

int main()
{
    Base* b0 = new (FastMemory()) Derived;
    b0->print();
    delete b0;

    Base* b1 = new Derived;
    b1->print();
    delete b1;

    Base* b2 = new (std::nothrow) Derived;
    b2->print();
    delete b2;

    int* p = new int[8];
    Base* b3 = new (p) Derived;
    b3->print();
    //delete b3;
    delete[] p;

    return 0;
}