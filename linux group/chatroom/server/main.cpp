#include "server.hpp"
#include "thread.hpp"

int main()
{
    server ser;
    Thread_Accept(ser);
    ser.Wait_In(); //
}