#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>

/**
 * @brief Singleton class that does not ensure a single creation
 *        when you have more than one thread in the system.
 */
class OldSingleton
{
public:

    static OldSingleton& getInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new OldSingleton;
        }
        return *_instance;
    }

private:

    OldSingleton()
    {
        std::cout << "OldSingleton created : " << this << std::endl;
    }

    OldSingleton(const OldSingleton&) = delete;
    OldSingleton& operator=(const OldSingleton&) = delete;

    static OldSingleton* _instance;
};

OldSingleton* OldSingleton::_instance = nullptr;

/**
 * @brief Singleton class that ensures a single creation at the begin.
 */
class Singleton
{
public:

    static Singleton& getInstance()
    {
        static Singleton singleton;
        return singleton;
    }

private:

    Singleton()
    {
        std::cout << "Singleton created : " << this << std::endl;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

int main()
{
    // Lambda function that executes every thread.
    auto func = [](std::string* address)
                {
                    Singleton& s = Singleton::getInstance();
                    //OldSingleton& s = OldSingleton::getInstance();
                    std::stringstream ss;
                    ss << &s;
                    *address = ss.str();
                };

    std::string t1Addr;
    std::thread t1(func, &t1Addr);
    std::string t2Addr;
    std::thread t2(func, &t2Addr);
    std::string t3Addr;
    std::thread t3(func, &t3Addr);
    std::string t4Addr;
    std::thread t4(func, &t4Addr);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << t1Addr << std::endl;
    std::cout << t2Addr << std::endl;
    std::cout << t3Addr << std::endl;
    std::cout << t4Addr << std::endl;

    return 0;
}
