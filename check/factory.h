/**
 * @author Bessone, Mariano <mariano.bessone@globant.com>
 *
 */

#ifndef FACTORY_H
#define FACTORY_H

#include <map>
//#include <mili/mili.h>

template <class Key, class Base>
class Factory
{
    template <typename ... Args>
    struct Creator
    {
        virtual Base* create(Args&& ... args) const = 0;
        virtual ~Creator() {}
    };

    std::map<Key, Creator*> _creators;

    template <class DerivedClass, typename ... Args>
    class ConcreteCreator : public Creator<Args ...>
    {
        virtual Base* create(Args&& ... args) const
        {
            return new DerivedClass(std::forward<Args>(args) ...);
        }
    };

public:
    template <class DerivedClass, typename ... Args>
    void register_factory(const Key& key, Args&& ... args)
    {
        _creators[key] = new ConcreteCreator<DerivedClass, std::forward<Args>(args) ...>;
    }

    template <typename ... Args>
    Base* new_class(const Key& key, Args&& ... args) const
    {
        typename std::map<Key, Creator*>::const_iterator it = _creators.find(key);

        if (it != _creators.end())
            return it->second->create(std::forward<Args>(args) ...);
        else
            return NULL;
    }

    ~Factory()
    {
        //mili::delete_container(_creators);
    }
};

#endif // FACTORY_H
