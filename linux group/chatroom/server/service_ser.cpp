#include "service_ser.hpp"
#include "../Serialization.hpp"
#include <sys/socket.h>
#include <cstring>
#include <iostream>
using std::string, std::cout, std::cin, std::endl;

void Getfd(int fd)
{
    string jso = Recv(fd);
    // int opt = ;
    switch (getopt(jso))
    {
    case 1:
        // 判断是否重名
        SendBool(fd, 1);
        UserTotal usr = New_User(jso);
        cout << "账号" << usr.account << "注册\n";
        Send(fd, To_Json_User(usr));
        cout << "返回用户" << usr.account << "个人信息\n";
        break;
        // case 2:

        //     break;
        // default://jump to case label???
        //     cout << "啊？" << endl;
        //     break;
    }
}

void Send(int fd, string jso)
{
    int numRead = jso.length();
    char *buffer = new char[numRead + 4];
    memcpy(buffer, &numRead, sizeof(int));
    memcpy(buffer + 4, jso.c_str(), numRead);
    send(fd, buffer, numRead + 4, 0);
}

void SendBool(int fd, bool flag)
{
    send(fd, (const void *)&flag, sizeof(bool), 0);
}

string Recv(int fd)
{
    char buffer[10000] = {};
    memset(&buffer, 0, sizeof(buffer));
    int reqLen;
    recv(fd, (void *)&reqLen, sizeof(int), 0);

    recv(fd, buffer, reqLen, 0);
    return string(buffer, reqLen);
}