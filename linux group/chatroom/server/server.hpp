#ifndef SERVER
#define SERVER
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <iostream>
#include <sys/epoll.h>
#include <unordered_map>
#include "thread_pool.hpp"
#define EPOLL_SIZE 100
class server
{
public:
    static std::unordered_map<int, int> ID_To_Fd; // User_To_Fd
    static int epfd;
    int lfd, cfd, optval, reqLen;
    char host[100], service[100];
    int hostlen = sizeof(host), servlen = sizeof(service);

    struct addrinfo hints;
    struct addrinfo *result, *rp;

    struct sockaddr addr; // 接收到的
    socklen_t addrlen = sizeof(addr);

    static struct epoll_event evadd;
    struct epoll_event evget[EPOLL_SIZE] = {};

    server();
    server(char *, char *);
    ~server(); // close（lfd）有问题

    void Accept(); // 需要对象 否则上面的变量都得static

    void Wait_In();
};

#endif