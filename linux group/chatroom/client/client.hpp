#ifndef CLIENT
#define CLIENT
#include <netdb.h>
#include <sys/socket.h>
#include <string>
#include <signal.h>
#include "../Serialization.hpp"
using std::string;
// 懒得传参就都是static，好像就不用弄成类的
class client
{
public:
    static int cfd, ID, frdID, grpID;
    static string account;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    static struct sigaction ign, respond;

    client();
    ~client();

    static void Send(string jso);
    static long long RecvInt();
    static string Recv();
    static string Recv_Online();
};

void sigioHandler(int sig);
#endif