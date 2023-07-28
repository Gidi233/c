#include "thread.hpp"
#include <thread>
using std::thread;

void Thread_Accept(server ser)
{
    // thread acpt(ser.Accept());

    thread acpt([&ser]()
                { ser.Accept(); }); // 不用lamda一直有问题？？？
    acpt.detach();
}