#ifndef SERVER
#define SERVER
#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/epoll.h>
#define EPOLL_SIZE 100
class server
{
public:
    int lfd, cfd, optval, reqLen, epfd;
    char host[100], service[100];
    int hostlen = sizeof(host), servlen = sizeof(service);

    struct addrinfo hints;
    struct addrinfo *result, *rp;

    struct sockaddr addr; // 接收到的
    socklen_t addrlen = sizeof(addr);

    struct epoll_event evadd = {
        .events = EPOLLHUP | EPOLLRDHUP | EPOLLIN,
        .data = {0},
    };
    struct epoll_event evget[EPOLL_SIZE] = {};

    server();

    void Accept(); // 需要对象 否则上面的变量都得static
    void Wait_In();
};

#endif