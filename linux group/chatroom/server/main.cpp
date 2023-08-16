#include "server.hpp"
// #include "thread.hpp"
#include "thread_pool.hpp"
#include "../user.hpp"
#include "database.hpp"

int main(int argc, char *argv[])
{
    if (argc == 1 || argc == 3)
    {
        if (argc == 1)
        {
            server ser;
            // Thread_Accept(ser);
            Database::Init(); // 往上放一行就不行？？？
            ser.Wait_In();    //
        }
        if (argc == 3)
        {
            server ser(argv[1], argv[2]);
            // Thread_Accept(ser);
            Database::Init(); // 往上放一行就不行？？？
            ser.Wait_In();    //
        }
    }
    else
        cout << "输的什么东西";
    exit(1);
}