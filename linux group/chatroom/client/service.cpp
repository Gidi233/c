#include "client.hpp"
#include "../Serialization.hpp"
#include "service.hpp"
#include <unistd.h>
#include <iostream>
using namespace std;

bool Main_Menu_Ser_Register()
{
    string account, password;
    system("clear");
    bool flag;
    while (1)
    {
        cout << "账户：";
        cin >> account;
        cout << "密码：";
        cin >> password;
        client::Send(From_Main(1, account, password));
        if (client::RecvBool())
        {
            cout << "注册成功" << endl;
            sleep(1); //
            return 1;
        }

        else
        {
            cout << "已注册" << endl
                 << "1.重新注册\n0.退出\n";
            cin >> flag;
            if (!flag)
                return 0;
        }
    }
}

bool Main_Menu_Ser_Login()
{
    string account, password;
    int cnt = 3;
    while (1)
    {
        cout << "账户：";
        cin >> account;
        cout << "密码：";
        cin >> password;
        client::Send(From_Main(2, account, password));
        if (client::RecvBool())
        {
            return 1;
        }
        else
        {
            cnt--;
            if (!cnt)
                return 0;
            cout << "还能尝试" << cnt << "次" << endl;
            continue;
        }
    }
}

void User_Ser_Exit(int ID)
{
    client::Send(From_Self(10, ID));
}

void Friend_Ser(int ID)
{
    UserBase frd;
    client::Send(From_Self(11, ID));
    int num = client::RecvInt();
    if (num)
    {
        for (int i = 0; i < num; i++)
        {
            frd = From_Json_UserBase(client::Recv());
            frd.toString();
            cout << "===========================================\n";
        }
    }
    else
    {
        cout << "当前无好友" << endl;
    }
}

void Add_Frd_Ser(int ID)
{
    int frdID;
    char choice;
    while (1)
    {
        system("clear");
        cout << "对方ID:";
        cin >> frdID;
        if (frdID == ID)
        {
            cout << "你小子酒吧进酒吧是吧（添加自己)\n";
            cout << "1.重新输入\n0.返回\n";
            cin >> choice;
            if (choice == '0')
                return;
            else
                continue;
        }
        client::Send(From_Frd(111, ID, frdID));
        switch (client::RecvInt())
        {
        case 0:
            cout << "添加成功\n";
            sleep(1);
            return;
            break;
        case 1:
            cout << "查无此人\n";
            break;
        case 2:
            cout << "你小子酒吧点炒菜是吧（重复添加)\n";
            break;
        default:
            cout << "啊？" << endl;
            break;
        }
        cout << "1.重新输入\n0.返回\n";
        cin >> choice;
        if (choice == '0')
            return;
    }
}

void Group_Ser(int ID)
{
    client::Send(From_Self(12, ID));
}

void To_User_Ser(int ID)
{
    client::Send(From_Self(100, ID));
}