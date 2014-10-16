#include <iostream>
#include "factory.h"

struct Shape
{
    virtual void draw() = 0;
};

class Circle : public Shape
{
    void draw()
    {
        std::cout << "Circle" << std::endl;
    }
};

class Square : public Shape
{
public:
    Square(float side) :
        _side(side)
    {}

private:

    void draw()
    {
        std::cout << "Square of size " << _side << std::endl;
    }

    float _side;
};

int main()
{
    Factory<std::string, Shape> myFactory;
    myFactory.register_factory<Circle>("circle");
    myFactory.register_factory<Square>("square", float);

    Shape* shape = myFactory.new_class("circle");
    shape->draw();

    Shape* shape2 = myFactory.new_class("square", 2.3f);
    shape2->draw();

    return 0;
}