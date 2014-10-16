#include <iostream>
#include <list>

struct P
{
    char first;
    int  n;
    char second;
};

int main()
{
    std::cout << sizeof(P) << std::endl;

    std::list<char> charList;
    charList.push_back('v');
    charList.push_back('h');
    charList.push_back('i');
    std::cout << sizeof(charList.front()) << std::endl;
    std::cout << sizeof(charList.begin()) << std::endl;
    std::cout << sizeof(charList) << std::endl;
    std::cout << sizeof(charList) * charList.size() << std::endl;

    return 0;
}