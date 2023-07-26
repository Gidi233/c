#include "service_ser.hpp"
#include "../Serialization.hpp"
#include "database.hpp"
#include "server.hpp"
#include <sys/socket.h>
#include <cstring>
#include <iostream>
using std::string, std::cout, std::cin, std::endl;

void Getfd(int fd)
{
    Database::Init();
    string jso = Recv(fd);
    string account, password;
    UserTotal usr;
    // int opt = ;
    switch (getopt(jso))
    {
    case 1:
        // 判断是否重名
        Get_Ac_Pa(jso, &account, &password);
        if (Database::User_Exist(account))
        {
            SendBool(fd, 0);
            return;
        }
        SendBool(fd, 1);
        usr = New_User(account, password);
        cout << "账号" << usr.account << "注册\n";
        Database::User_In(account, To_Json_User(usr));
        Send(fd, To_Json_User(usr));
        cout << "返回用户" << usr.account << "个人信息\n";
        server::Fd_To_User.emplace(fd, account);
        break;
    case 2:
        Get_Ac_Pa(jso, &account, &password);
        usr = From_Json_User(Database::User_Out(account));
        if (usr.password == password) //
        {
            Change_isLogin_Ser(account);
            // usr = From_Json_User(Database::User_Out(account)); //
            SendBool(fd, 1);
            Send(fd, Database::User_Out(account)); // To_Json_User(usr)
            server::Fd_To_User.emplace(fd, account);
        }
        else
            SendBool(fd, 0);

        break;
    case 10:
        Get_Ac_Pa(jso, &account, nullptr); //
        Change_isLogin_Ser(account);
        // SendBool(fd, Change_isLogin_Ser(account));
        break;

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
    memset(buffer, 0, sizeof(buffer));
    int reqLen;
    recv(fd, (void *)&reqLen, sizeof(int), 0);

    recv(fd, buffer, reqLen, 0);
    return string(buffer, reqLen);
}

UserTotal New_User(string account, string password)
{
    return UserBase(account, password);
}

bool Change_isLogin_Ser(string account)
{
    string jso = Change_isLogin(Database::User_Out(account));
    return Database::User_In(account, jso);
}