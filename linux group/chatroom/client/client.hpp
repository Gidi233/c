#ifndef CLIENT
#define CLIENT
#include <netdb.h>
#include <sys/socket.h>
#include <string>
#include "../Serialization.hpp"
using std::string;
// 懒得传参就都是static，好像就不用弄成类的
class client
{
public:
    static int cfd, oppositeID;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    // char buffer[10000] = {};

    client();
    ~client();

    static void Send(string jso);
    static int RecvInt(); // 只有一个recv 收的是json 函数分为num str
    static string Recv();
};

#endif