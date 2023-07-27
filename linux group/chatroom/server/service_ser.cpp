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
    // Database::Init(); //???
    string jso = Recv(fd);
    string account, password;
    int ID, oppositeID, chatID;
    UserTotal usr;
    switch (getopt(jso))
    {

    case 1:
        // 判断是否重名
        Get_Info(jso, nullptr, &account, &password, nullptr);
        if (Database::User_Exist_Account(account))
        {
            SendBool(fd, 0);
            return;
        }
        SendBool(fd, 1);
        usr = New_User(account, password);
        cout << "账号" << usr.ID << "注册\n";
        Database::Set_Account_To_ID(usr.ID, account);
        Database::User_In(usr.ID, To_Json_User(usr));
        Send(fd, To_Json_User(usr));
        // cout << "返回用户" << usr.ID << "个人信息\n";
        server::ID_To_Fd.emplace(usr.ID, fd);
        break;
    case 2:
        Get_Info(jso, nullptr, &account, &password, nullptr);
        usr = From_Json_UserTotal(Database::User_Out(Database::Get_Account_To_ID(account)));
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
        Get_Info(jso, &ID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        if (usr.frd.empty())
        {
            SendInt(fd, 0);
        }
        else
        {
            SendInt(fd, usr.frd.size());
            for (const auto &FID : usr.frd) // std::pair<int, int>
            {
                Send(fd, Database::User_Out(FID.first));
            }
        }
        cout << "返回用户" << ID << "好友信息\n";
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
        Get_Info(jso, &ID, nullptr, nullptr, nullptr);
        Change_isLogin_Ser(ID);
        server::ID_To_Fd.erase(ID);
        cout << "用户" << ID << "退出\n";
        // SendBool(fd, Change_isLogin_Ser(account));
        break;

    case 111:
        Get_Info(jso, &ID, nullptr, nullptr, &oppositeID); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        if (!Database::User_Exist_ID(oppositeID))
        {
            SendInt(fd, 1);
        }

        // 检查是否找到了这个值
        if (usr.frd.find(oppositeID) != usr.frd.end())
        {
            SendInt(fd, 2);
            // cout << "找到值：" << *it << std::endl;
        }
        chatID = Database::Get_ChatID();
        Database::User_In(ID, Add_Friend(oppositeID, Database::User_Out(ID), chatID));
        Database::User_In(oppositeID, Add_Friend(ID, Database::User_Out(oppositeID), chatID)); //
        SendInt(fd, 0);
        cout << "返回用户" << ID << "好友信息\n";
        break;

    case 100:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr);
        Send(fd, Database::User_Out(ID));

        break;

    default: // jump to case label???
        cout << "啊？" << endl;
        break;
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

void SendInt(int fd, int num)
{
    send(fd, (const void *)&num, sizeof(int), 0);
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
