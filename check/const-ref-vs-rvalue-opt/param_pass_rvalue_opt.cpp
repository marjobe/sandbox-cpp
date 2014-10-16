#include <iostream>

struct M
{

    void set(std::string&& name) noexcept
    {
        attr = std::move(name);
    }

    std::string attr;

};

int main()
{
    M m;
    m.set("pepe");
    std::cout << m.attr << std::endl;

    return 0;
}
