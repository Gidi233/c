#include "server.hpp"
#include "thread.hpp"
#include "../user.hpp"
#include "database.hpp"

int main()
{
    server ser;
    Database::Init();
    Thread_Accept(ser);
    ser.Wait_In(); //
}