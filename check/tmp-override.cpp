#include <iostream>

template <class Base>
struct First : public Base
{
    std::string call() const
    {
        return "First";
    }
};

template <class Base>
struct Second : public Base
{
    std::string call() const
    {
        return "Second";
    }
};

struct Last
{
    std::string call() const
    {
        return "Last";
    }
};

typedef First<Second<Last>> TriClass;

template <bool Flag, class Base>
struct Variant : public Base {};

template <class Base>
struct Variant<true, Base> : public Base
{
    bool variantTrue() const
    {
        return true;
    }
};

template <class Base>
struct Variant<false, Base> : public Base
{
    bool variantFalse() const
    {
        return true;
    }
};

int main()
{
    TriClass t;
    std::cout << t.call() << std::endl;

    struct Nothing {};

    Variant<true, Nothing> vt;
    vt.variantTrue();
    //vt.variantFalse();

    Variant<false, Nothing> vf;
    //vf.variantTrue();
    vf.variantFalse();    

    return 0;
}