#include <iostream>

template <typename T>
constexpr T calculateSomething(T n)
{
    return (n < T(1)) ? T(0) : ((n < T(10)) ? n : n + T(10));
}

template <>
constexpr std::string calculateSomething(std::string n)
{
    return n;
}

int main()
{
    static_assert(calculateSomething(0) == 0, "FAIL");
    static_assert(calculateSomething(0.0) == 0.0, "FAIL");
    static_assert(calculateSomething('a') == 'k', "FAIL");
    //static_assert(calculateSomething(std::string("pepe")) == std::string("pepe10"), "FAIL");

    //auto res = calculateSomething(13.4f);
    auto res = calculateSomething(std::string("pepe"));
    std::cout << res << std::endl;

    return 0;
}