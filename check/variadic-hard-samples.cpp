#include <iostream>
#include <map>

template <class Key, class Base>
class Factory
{

    struct Creator
    {
        virtual Base* create() const = 0;
        virtual ~Creator() {}
    };

    template <class DerivedClass, typename ... Args>
    class ConcreteCreator : public Creator
    {
    public:

        ConcreteCreator(Args&& ... args) :
            _tuple(std::forward<Args>(args) ...)
        {}

    private:

        virtual Base* create() const
        {
            return new DerivedClass(_tuple ...);
        }

        std::tuple<Args ...> _tuple;

    };


    std::map<Key, Creator*> _creators;

public:

    template <class DerivedClass, typename ... Args>
    void register_factory(const Key& key, Args&& ... args)
    {
        _creators[key] = new ConcreteCreator<DerivedClass, Args ...>(std::forward<Args>(args) ...);
    }

    Base* new_class(const Key& key) const
    {
        typename std::map<Key, Creator*>::const_iterator it = _creators.find(key);

        if (it != _creators.end())
            return it->second->create();
        else
            return NULL;
    }

};


/*********************************************************/
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
/*********************************************************/

int main()
{
    Factory<std::string, Shape> myFactory;
    myFactory.register_factory<Circle>("circle");
    myFactory.register_factory<Square, float>("square", 2.5f);

    Shape* shape = myFactory.new_class("circle");
    shape->draw();

    Shape* shape2 = myFactory.new_class("square");
    shape2->draw();
    
    return 0;
}