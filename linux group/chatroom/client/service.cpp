#include "client.hpp"
#include "../Serialization.hpp"
#include "service.hpp"
#include "../event.hpp"
#include <unistd.h>
#include <iostream>
using namespace std;

int Main_Menu_Ser_Register()
{
    string account, password;
    int ID;
    char flag;
    while (1)
    {
        system("clear");
        cout << "账户：";
        cin >> account;
        cout << "密码：";
        cin >> password;
        // 加个再次输入密码
        client::Send(From_Main(Register, account, password));
        if ((ID = client::RecvInt()))
        {
            cout << "注册成功" << endl;
            sleep(1); //
            return ID;
        }

        else
        {
            cout << "已注册" << endl
                 << "1.重新注册\n0.退出\n";
            cin >> flag;
            if (flag == '0')
                return 0;
        }
    }
}

int Main_Menu_Ser_Login()
{
    string account, password;
    int cnt = 3;
    int ID;
    while (1)
    {
        // system("clear");
        cout << "账户：";
        cin >> account;
        cout << "密码：";
        cin >> password;
        client::Send(From_Main(Login, account, password));
        if ((ID = client::RecvInt()))
        {
            return ID;
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

UserBase Get_User_Ser(int ID)
{
    client::Send(From_Self(User, ID));
    return From_Json_UserBase(client::Recv());
}

void User_Ser_Exit(int ID)
{
    client::Send(From_Self(Exit, ID));
}

void Friend_Ser(int ID)
{
    UserBase frd;
    client::Send(From_Self(Frd_List, ID));
    int num = client::RecvInt();
    if (num)
    {
        for (int i = 0; i < num; i++)
        {
            frd = From_Json_UserBase(client::Recv());
            frd.toString();
            cout << "==================================================\n";
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
        client::Send(From_Frd(Add_Frd, ID, frdID));
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

void Del_Frd_Ser(int ID)
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
            cout << "你小子酒吧进酒吧是吧（删自己)\n";
            cout << "1.重新输入\n0.返回\n";
            cin >> choice;
            if (choice == '0')
                return;
            else
                continue;
        }
        client::Send(From_Frd(Del_Frd, ID, frdID));
        switch (client::RecvInt())
        {
        case 0:
            cout << "删除成功\n";
            sleep(1);
            return;
            break;
        case 1:
            cout << "并无该好友\n";
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
    client::Send(From_Self(Grp_List, ID));
}
