#include <iostream>

struct M
{

    void set(const std::string& name)
    {
        attr = name;
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
