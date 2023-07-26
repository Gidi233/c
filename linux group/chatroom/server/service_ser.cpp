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
    int ID;
    UserTotal usr;
    switch (getopt(jso))
    {
    case 1:
        // 判断是否重名
        Get_Ac_Pa(jso, nullptr, &account, &password);
        if (Database::User_Exist(account))
        {
            SendBool(fd, 0);
            return;
        }
        SendBool(fd, 1);
        usr = New_User(account, password);
        cout << "账号" << usr.ID << "注册\n";
        Database::Set_Account_ID(usr.ID, account);
        Database::User_In(usr.ID, To_Json_User(usr));
        Send(fd, To_Json_User(usr));
        cout << "返回用户" << usr.ID << "个人信息\n";
        server::ID_To_Fd.emplace(usr.ID, fd);
        break;
    case 2:
        Get_Ac_Pa(jso, nullptr, &account, &password);
        usr = From_Json_User(Database::User_Out(Database::Get_Account_ID(account)));
        if (usr.password == password)
        {
            cout << "账号" << usr.ID << "登录\n";
            Change_isLogin_Ser(usr.ID);
            SendBool(fd, 1);
            Send(fd, Database::User_Out(usr.ID));
            server::ID_To_Fd.emplace(usr.ID, fd);
        }
        else
            SendBool(fd, 0);

        break;
    case 11:
        Get_Ac_Pa(jso, &ID, nullptr, nullptr); //

        cout << "返回用户" << account << "好友信息\n";
        // SendBool(fd, Change_isLogin_Ser(account));
        break;

    // case 12:
    //     Get_Ac_Pa(jso, &account, nullptr); //
    //     server::User_To_Fd.erase(account);
    //     cout << "用户" << account << "退出\n";
    //     // SendBool(fd, Change_isLogin_Ser(account));
    //     break;

    // case 19:
    //     Get_Ac_Pa(jso, &account, nullptr); //
    //     server::User_To_Fd.erase(account);
    //     cout << "用户" << account << "退出\n";
    //     // SendBool(fd, Change_isLogin_Ser(account));
    //     break;
    case 10:
        Get_Ac_Pa(jso, &ID, nullptr, nullptr); //
        // ID = Database::Get_Account_ID(account);
        Change_isLogin_Ser(ID);
        server::ID_To_Fd.erase(ID);
        cout << "用户" << ID << "退出\n";
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

bool Change_isLogin_Ser(int ID)
{
    string jso = Change_isLogin(Database::User_Out(ID));
    return Database::User_In(ID, jso);
}