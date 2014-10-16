#include <iostream>

// Base case.
unsigned int calculateSize()
{
    return 0u;
}

// Inductive case.
template <typename Head, typename... Tail>
unsigned int calculateSize(const Head& head, const Tail&... tail)
{
    return sizeof(head) + calculateSize(tail...);
}

template <typename T>
class Constructor
{
public:

    template <typename... Arg>
    Constructor(Arg&& ...arg) :
        _member(std::forward<Arg>(arg)...)
    {}

    inline T& getMember()
    {
        return _member;
    }

private:

    T _member;
};

int main()
{
    struct Pepe
    {
        int number;
        float rate;
    };

    const Pepe p({1, 4.5f});
    const int n = 34;
    const char c = 'e';
    const std::string name("01234567890123456789");
    const char name2[] = "01234";

    std::cout << calculateSize(p, n, c, name, name2) << std::endl;

    struct Foo
    {
        Foo(const std::string& name, int num) :
            name(name),
            num(num)
        {}

        std::string     name;
        int             num;
    };

    Constructor<Foo> fooConstructor("Juan", 15);
    Foo& foo = fooConstructor.getMember();

    std::cout << foo.name << ", " << foo.num << std::endl;

    return 0;
}