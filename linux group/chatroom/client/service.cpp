#include "client.hpp"
#include "../Serialization.hpp"
#include "service.hpp"
#include <unistd.h>
#include <iostream>
using namespace std;

static string account, password;

bool Main_Menu_Ser_Register()
{
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

bool User_Ser()
{
}