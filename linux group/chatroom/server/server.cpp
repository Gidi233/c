#include "server.hpp"
#include "service_ser.hpp"
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
using std::string, std::cout, std::cin, std::endl;
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
        // 重用ip地址
        if (bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break; /* Success */

        /* bind() failed: close this socket and try next address */

        close(lfd);
    }

    if (rp == NULL)
        std::cout << strerror(errno);

    if (listen(lfd, 5) == -1)
        std::cout << strerror(errno);

    freeaddrinfo(result);

    epfd = epoll_create(EPOLL_SIZE);
}

void server::Accept()
{
    while (1)
    {
        memset(&host, 0, hostlen);
        memset(&service, 0, servlen);
        cfd = accept(lfd, &addr, &addrlen);
        getnameinfo(&addr, addrlen, host, hostlen, service, servlen, 0);
        cout << host << ":" << service << "连接\n";
        if (cfd == -1)
        {
            std::cout << strerror(errno);
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
    memset(&evget, 0, sizeof(evget));
    while (1)
    {

        int num = epoll_wait(epfd, evget, EPOLL_SIZE, -1);
        for (int i = 0; i < num; i++)
        {
            if (evget[i].events == EPOLLIN)
                Getfd(evget[i].data.fd);
            else if (evget[i].events == EPOLLHUP | EPOLLRDHUP)
            {
                epoll_ctl(epfd, EPOLL_CTL_DEL, evget[i].data.fd, 0);
            }
        }
    }
}