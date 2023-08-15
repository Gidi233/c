
#include <netdb.h>
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include "client.hpp"
#include "../Message.hpp"
using namespace std;

int client::cfd = -1, client::frdID = -1, client::grpID = -1, client::ID = -1;
string client::account = "";
struct sigaction client::ign, client::respond;

client::client()
{
    int fd;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC; /* IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV; //

    getaddrinfo("127.0.0.1", "50000", &hints, &result);

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {

        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd == -1)
            continue; /* On error, try next address */

        if (connect(fd, rp->ai_addr, rp->ai_addrlen) != -1)
            break; /* Success */

        /* Connect failed: close this socket and try next address */

        close(fd);
    }
    cfd = fd; //???
    freeaddrinfo(result);

    sigemptyset(&ign.sa_mask);
    ign.sa_handler = SIG_IGN;
    sigemptyset(&respond.sa_mask);
    respond.sa_flags = SA_RESTART;
    respond.sa_handler = sigioHandler;
    sigaction(SIGIO, &ign, 0);
    fcntl(cfd, F_SETOWN, getpid());
    int flags = fcntl(cfd, F_GETFL);
    fcntl(cfd, F_SETFL, flags | O_ASYNC);
}

client::~client()
{
    close(cfd);
}

void client::Send(string jso)
{
    sigaction(SIGIO, &ign, 0);
    int numRead = jso.length();
    char *buffer = new char[numRead + 4];
    memcpy(buffer, &numRead, sizeof(int));
    memcpy(buffer + 4, jso.c_str(), numRead);
    send(cfd, buffer, numRead + 4, 0);
    // cout << send(cfd, buffer, numRead + 4, 0) << endl;
    delete[] buffer;
}

long long client::RecvInt()
{
    return Get_Num(Recv());
}

string client::Recv()
{
    int reqLen;
    recv(cfd, (void *)&reqLen, sizeof(int), 0);
    char *buffer = new char[reqLen];
    recv(cfd, buffer, reqLen, 0);
    string res(buffer, reqLen);
    delete[] buffer;
    string ans = Get_Type(res);    // 在这里检测是实时信息还是回应，实时消息再调Recv
    sigaction(SIGIO, &respond, 0); // 重复调用，改成迭代？
    return ans;
}

string client::Recv_Online()
{
    int reqLen;
    recv(cfd, (void *)&reqLen, sizeof(int), 0);
    char *buffer = new char[reqLen];
    recv(cfd, buffer, reqLen, 0);
    string res(buffer, reqLen);
    delete[] buffer;
    return res;
}

void sigioHandler(int sig)
{
    Message msg = From_Json_Msg(client::Recv_Online()); // 改成非阻塞一直读？
    msg.toString();                                     // 在信号处理程序中输出（好像）会刷新输出流（还是什么来着）
    // 在这里开个进程输出？？？
}
