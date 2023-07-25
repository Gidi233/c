#ifndef CLIENT
#define CLIENT
#include <netdb.h>
#include <sys/socket.h>
#include <string>
using std::string;
class client
{
public:
    static int cfd;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    // char buffer[10000] = {};

    client();
    ~client();

    static void Send(string jso);
    static bool RecvBool();
    static string Recv();
};

#endif