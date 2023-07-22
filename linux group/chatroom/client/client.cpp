
#include <netdb.h>
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "client.hpp"
using namespace std;

int client::cfd = -1;

client::client()
{
    int fd;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_family = AF_UNSPEC; /* IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV; // ���ص������ֽ���

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
    cfd = fd;
    freeaddrinfo(result);
}

client::~client()
{
    close(cfd);
}

void client::Send(string jso)
{

    int numRead = jso.length();
    char *buffer = new char[numRead + 4];
    memcpy(buffer, &numRead, sizeof(int));
    memcpy(buffer + 4, jso.c_str(), numRead);
    send(cfd, buffer, numRead + 4, 0);
    delete buffer;
}

bool client::RecvBool()
{
    bool res;
    recv(cfd, (void *)&res, sizeof(bool), 0);
    return res;
}

string client::Recv()
{
    int reqLen;
    recv(cfd, (void *)&reqLen, sizeof(int), 0);
    char *buffer = new char[reqLen];
    recv(cfd, buffer, reqLen, 0);
    string res(buffer, reqLen);
    delete buffer;
    return res;
}
