#include "server.hpp"
// #include "thread.hpp"
#include "thread_pool.hpp"
#include "../user.hpp"
#include "database.hpp"

int main()
{
    server ser;
    // Thread_Accept(ser);
    Database::Init(); // 往上放一行就不行？？？
    ser.Wait_In();    //
}