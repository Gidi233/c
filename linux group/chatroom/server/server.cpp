#include "server.hpp"
#include "service_ser.hpp"
#include "database.hpp"
#include "thread_pool.hpp"
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
using std::string, std::cout, std::cin, std::endl;

// std::unordered_map<int, int> server::ID_To_Fd = {};//有的话多重定义？？？  要不然拿函数包一层

int server::epfd = -1;
struct epoll_event server::evadd = {
    .events = EPOLLHUP | EPOLLRDHUP | EPOLLIN | EPOLLET,
    .data = {0},
};

server::server()
{

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;                  /*IPv4 or IPv6 */
    hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV; // 通配地址
    /* Wildcard IP address; service name is numeric */

    if (getaddrinfo(NULL, "50000", &hints, &result) != 0)
        std::cout << strerror(errno);

    optval = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        lfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (lfd == -1)
            continue; /* On error, try next address */

        if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
            std::cout << strerror(errno);
        if (setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) < 0)
        {
            perror("setsockopt error");
            exit(1);
        }
        if (setsockopt(lfd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval)) < 0)
        {
            perror("setsockopt error");
            exit(1);
        }
        int keepIdle = 30;    // 如果30秒内没有数据交流,则发送心跳包
        int keepInterval = 5; // 每5秒发送一次心跳包
        int keepCount = 3;    // 最多发送3次心跳包

        setsockopt(lfd, IPPROTO_TCP, TCP_KEEPIDLE, (void *)&keepIdle, sizeof(keepIdle));
        setsockopt(lfd, IPPROTO_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
        setsockopt(lfd, IPPROTO_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));

        // 重用ip地址
        if (bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break; /* Success */

        /* bind() failed: close this socket and try next address */

        close(lfd);
    }

    if (rp == NULL)
        cout << strerror(errno);

    if (listen(lfd, 100) == -1)
        cout << strerror(errno);

    freeaddrinfo(result);

    epfd = epoll_create(EPOLL_SIZE);
}

server::server(char *addr, char *port)
{

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;                  /*IPv4 or IPv6 */
    hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV; // 通配地址
    /* Wildcard IP address; service name is numeric */

    if (getaddrinfo(addr, port, &hints, &result) != 0)
        std::cout << strerror(errno);

    optval = 1;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        lfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (lfd == -1)
            continue; /* On error, try next address */

        if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
            std::cout << strerror(errno);
        if (setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) < 0)
        {
            perror("setsockopt error");
            exit(1);
        }
        if (setsockopt(lfd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval)) < 0)
        {
            perror("setsockopt error");
            exit(1);
        }

        int keepIdle = 30;    // 如果30秒内没有数据交流,则发送心跳包
        int keepInterval = 5; // 每5秒发送一次心跳包
        int keepCount = 3;    // 最多发送3次心跳包

        setsockopt(lfd, IPPROTO_TCP, TCP_KEEPIDLE, (void *)&keepIdle, sizeof(keepIdle));
        setsockopt(lfd, IPPROTO_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
        setsockopt(lfd, IPPROTO_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));

        // 重用ip地址
        if (bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break; /* Success */

        /* bind() failed: close this socket and try next address */

        close(lfd);
    }

    if (rp == NULL)
        cout << strerror(errno);

    if (listen(lfd, 100) == -1)
        cout << strerror(errno);

    freeaddrinfo(result);

    epfd = epoll_create(EPOLL_SIZE);
}

server::~server()
{
    Database::Close(); // 关闭数据库
}

void server::Accept()
{
    while (1)
    {
        memset(host, 0, hostlen);
        memset(service, 0, servlen);
        memset(&addr, 0, addrlen); // 放到里面段错误，外面无限循环？？
        // cout << "lfd1:" << lfd << endl;
        cfd = accept(lfd, &addr, &addrlen); // lfd自增了？？
        // cout << "lfd2:" << lfd << endl;
        getnameinfo(&addr, addrlen, host, hostlen, service, servlen, 0);
        cout << host << ":" << service << "连接\n";
        if (cfd == -1)
        {
            cout << "cfd" << cfd << strerror(errno) << endl;
        }
        int flags = fcntl(cfd, F_GETFL, 0);
        fcntl(cfd, F_SETFL, flags | O_NONBLOCK);
        evadd.data.fd = cfd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &evadd);
    }
    return;
}

void server::Wait_In()
{
    memset(evget, 0, sizeof(evget));
    int fd;
    ThreadPool pool(15);
    pool.init();
    pool.submit([this]()
                { this->Accept(); }); //
    while (1)
    {
        int num = epoll_wait(epfd, evget, EPOLL_SIZE, -1);
        if (num == -1)
        {
            cout << "num:" << num << strerror(errno) << endl;
        }
        for (int i = 0; i < num; i++)
        {
            if (evget[i].events == EPOLLIN) // 不应该是&吗
            {
                // Getfd(evget[i].data.fd);
                pool.submit(Getfd, &evget[i].data.fd); // 直接传值的话有这个问题：error: cannot bind packed field ‘((server*)this)->server::evget[i].epoll_event::data.epoll_data::fd’ to ‘int&’
            }
            else if (evget[i].events == EPOLLHUP | EPOLLRDHUP) // EPOLLRDHUP没起作用？
            {
                cout << "连接" << evget[i].data.fd << "断开\n";
                epoll_ctl(epfd, EPOLL_CTL_DEL, evget[i].data.fd, 0);
                auto it = find_if(ID_To_Fd.begin(), ID_To_Fd.end(),
                                  [this, i](const pair<int, int> &p)
                                  { return p.second == evget[i].data.fd; });
                if (it != ID_To_Fd.end())
                {
                    server::ID_To_Fd.erase(it);
                }
                close(evget[i].data.fd);
            }
        }
    }
}
