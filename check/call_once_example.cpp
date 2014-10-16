#include <iostream>
#include <thread>
#include <mutex>
 
void do_once(std::once_flag* flag, const std::string& threadName)
{
    std::call_once(*flag, [&threadName](){ std::cout << threadName << " : Called once" << std::endl; });
}

/****/

std::once_flag flag2;
 
inline void may_throw_function(bool do_throw)
{
  // only one instance of this function can be run simultaneously
  if (do_throw) {
    std::cout << "throw\n"; // this message may be printed from 0 to 3 times
    // if function exits via exception, another function selected
    throw std::exception();
  }
 
  std::cout << "once\n"; // printed exactly once, it's guaranteed that
      // there are no messages after it
}
 
inline void do_once_throw(bool do_throw)
{
  try {
    std::call_once(flag2, may_throw_function, do_throw);
  }
  catch (...) {
  }
}

/****/

int main()
{
    std::once_flag flag;
    std::cout << "First example: without throw" << std::endl;
    std::thread t1(do_once, &flag, "t1");
    std::thread t2(do_once, &flag, "t2");
    std::thread t3(do_once, &flag, "t3");
    std::thread t4(do_once, &flag, "t4");
 
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Second example: with throw" << std::endl;
    std::thread t5(do_once_throw, true);
    std::thread t6(do_once_throw, true);
    std::thread t7(do_once_throw, false);
    std::thread t8(do_once_throw, true);
 
    t5.join();
    t6.join();
    t7.join();
    t8.join();
}
