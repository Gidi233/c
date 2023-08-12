#include "client.hpp"
#include "../Serialization.hpp"
#include "service.hpp"
#include "../Message.hpp"
#include "../event.hpp"
#include <list>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int Get_Int()
{
    string str;
    char *endptr;
    int num;
    while (1)
    {
        cin >> str;
        num = strtol(str.c_str(), &endptr, 10);

        if (*endptr != '\0')
        {
            cout << "你输得什么东西！嗯？\n再给你次机会：";
        }
        else
        {
            return num;
        }
    }
}

int Main_Menu_Ser_Register()
{
    string account, password;
    int ID;
    int choice;
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
            sigaction(SIGIO, &client::ign, 0);
            cout << "注册成功" << endl;
            sleep(1); //
            return ID;
        }

        else
        {
            cout << "已注册" << endl
                 << "1.重新注册\n0.退出\n";
            choice = Get_Int();
            if (!choice)
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
            sigaction(SIGIO, &client::ign, 0);
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

set<Message, MessageComparator> Get_Frd_ManageList_Ser(int ID)
{
    client::Send(From_Self(Get_Frd_ManageList, ID));
    return From_Json_Manage_List(To_Manage(client::Recv()));
}

void Friend_Ser(int ID)
{
    client::Send(From_Self(Frd_List, ID));
    From_Json_Frdlist(client::Recv());
}

void Add_Frd_Ser(int ID)
{
    int frdID;
    int choice;
    while (1)
    {
        system("clear");
        cout << "对方ID:";
        frdID = Get_Int();
        if (frdID == ID)
        {
            cout << "你小子酒吧进酒吧是吧（添加自己)\n";
            cout << "1.重新输入\n0.返回\n";
            choice = Get_Int();
            if (!choice)
                return;
            else
                continue;
        }
        client::Send(From_Frd(Send_Add_Frd, ID, frdID));
        switch (client::RecvInt())
        {
        case 0:
            cout << "发送申请成功\n";
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
        choice = Get_Int();
        if (!choice)
            return;
    }
}

void Del_Frd_Ser(int ID)
{
    int frdID;
    int choice;
    while (1)
    {
        system("clear");
        cout << "对方ID:";
        frdID = Get_Int();
        if (frdID == ID)
        {
            cout << "你小子酒吧进酒吧是吧（删自己)\n";
            cout << "1.重新输入\n0.返回\n";
            choice = Get_Int();
            if (!choice)
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
        choice = Get_Int();
        if (!choice)
            return;
    }
}

void Send_Msg_Ser(UserBase usr)
{
    int frdID;
    int num;
    int choice;
    while (1)
    {
        system("clear");
        cout << "对方ID:";
        frdID = Get_Int();
        if (frdID == usr.ID)
        {
            cout << "你小子跟自己唠是吧\n";
            cout << "1.重新输入\n0.返回\n";
            choice = Get_Int();
            if (!choice)
                return;
            else
                continue;
        }
        client::Send(From_Frd(Able_To_Send_Frd, usr.ID, frdID));
        num = client::RecvInt();
        if (!num)
            break;
        if (num == 1)
            cout << "你已將對方屏蔽\n";
        if (num == 2)
            cout << "對方已將你屏蔽\n";
        if (num == 3)
            cout << "并无该好友\n";
        cout << "1.重新输入\n0.返回\n";
        choice = Get_Int();
        if (!choice)
            return;
    }
    client::frdID = frdID;
    system("clear");
    cout << "聊天界面\n";
    client::Send(From_Frd(Get_frdChat, usr.ID, frdID));
    From_Json_Chat(client::Recv());
    string str;
    while (1)
    {
        cin >> str;
        if (str == "\\q")
        {
            client::frdID = -1;
            return;
        }
        cout << "\033[1A\x1b[2K\r";
        Message msg(Sendmsg_Tofrd, usr.ID, usr.account, frdID, str, gettime());
        msg.toString();
        client::Send(To_Json_Msg(msg)); // 在这里收回应是否把你屏蔽
        sigaction(SIGIO, &client::respond, 0);
    }
}

void Block_Frd_Ser(int ID)
{
    int frdID;
    int choice;
    while (1)
    {
        system("clear");
        cout << "对方ID:";
        frdID = Get_Int();
        if (frdID == ID)
        {
            cout << "你小子酒吧进酒吧是吧（屏蔽自己)\n";
            cout << "1.重新输入\n0.返回\n";
            choice = Get_Int();
            if (!choice)
                return;
            else
                continue;
        }
        client::Send(From_Frd(Block_Frd, ID, frdID));
        switch (client::RecvInt())
        {
        case 0:
            cout << "修改成功\n";
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
        choice = Get_Int();
        if (!choice)
            return;
    }
}

void Search_Frd_Ser(int ID)
{
    string account;
    int choice;
    int ans;
    while (1)
    {
        system("clear");
        cout << "对方账户:";
        cin >> account;
        client::Send(From_Frd_Account(Search_Frd, account));
        if ((ans = client::RecvInt()))
        {
            cout << account << "的ID为" << ans << endl;
            sleep(1);
            return;
        }
        cout << "该用户不存在\n";
        cout << "1.重新输入\n0.返回\n";
        choice = Get_Int();
        if (!choice)
            return;
    }
}

void Group_Ser(int ID)
{
    client::Send(From_Self(Grp_List, ID));
    From_Json_Grplist(client::Recv());
}

void New_Grp_Ser(int ID)
{
    string name;
    int choice;
    while (1)
    {
        system("clear");
        cout << "群名：";
        cin >> name;
        client::Send(From_Grp_Name(New_Grp, ID, name));
        if ((client::RecvInt()))
        {
            cout << "建群成功" << endl;
            sleep(1); //
            return;
        }
        else
        {
            cout << "已存在该名称" << endl
                 << "1.重新建\n0.退出\n";
            choice = Get_Int();
            if (!choice)
                return;
        }
    }
}

void Add_Grp_Ser(int ID)
{
    int GID, ans;
    int choice;
    while (1)
    {
        system("clear");
        cout << "输入申请要加入的群：";
        GID = Get_Int();
        client::Send(From_Grp(Send_Add_Grp, ID, GID));
        ans = client::RecvInt();
        if (!ans)
        {
            cout << "成功发送申请" << endl;
            sleep(1);
            return;
        }
        if (ans == 1)
        {
            cout << "不存在该群" << endl;
        }
        if (ans == 2)
        {
            cout << "已加入该群" << endl;
        }
        cout << "1.重新输入\n0.退出\n";
        choice = Get_Int();
        if (!choice)
            return;
    }
}

int Choose_Grp_Ser(int ID)
{
    int GID;
    int choice;
    while (1)
    {
        system("clear");
        cout << "GID：";
        GID = Get_Int();
        client::Send(From_Grp(Choose_Grp, ID, GID));
        if ((client::RecvInt()))
        {
            return GID;
        }
        else
        {
            cout << "未加入该群" << endl
                 << "1.重新输入\n0.退出\n";
            choice = Get_Int();
            if (!choice)
                return 0;
        }
    }
}

void In_Grp_Ser(int GID)
{
    client::Send(From_Grp_Only(Grp_Member_List, GID));
    From_Json_Grp_Member_List(client::Recv());
}

void Add_Manager_Ser(int GID)
{
    system("clear");
    int otherUsrID;
    int choice;
    if (Check_Authority_Ser(GID) != 2)
    {
        cout << "你什么身份！？\n";
        sleep(1);
        return;
    }
    while (1)
    {
        system("clear");
        cout << "对方ID:";
        otherUsrID = Get_Int();
        if (otherUsrID == client::ID)
        {
            cout << "第一次见给自己降权的\n";
            cout << "1.重新输入\n0.返回\n";
            choice = Get_Int();
            if (!choice)
                return;
            else
                continue;
        }
        client::Send(From_Grp_Usr(Add_Manager, client::ID, GID, otherUsrID));
        switch (client::RecvInt())
        {
        case 0:
            cout << "添加管理员成功\n";
            sleep(1);
            return;
            break;
        case 1:
            cout << "无此群员\n";
            break;
        case 2:
            cout << "该成员就是管理员\n";
            break;
        default:
            cout << "啊？" << endl;
            break;
        }
        cout << "1.重新输入\n0.返回\n";
        choice = Get_Int();
        if (!choice)
            return;
    }
}

void Del_Manager_Ser(int GID)
{
    system("clear");
    int otherUsrID;
    int choice;
    if (Check_Authority_Ser(GID) != 2)
    {
        cout << "你什么身份！？\n";
        sleep(1);
        return;
    }
    while (1)
    {
        system("clear");
        cout << "对方ID:";
        otherUsrID = Get_Int();
        if (otherUsrID == client::ID)
        {
            cout << "第一次见给自己降权的\n";
            cout << "1.重新输入\n0.返回\n";
            choice = Get_Int();
            if (!choice)
                return;
            else
                continue;
        }
        client::Send(From_Grp_Usr(Del_Manager, client::ID, GID, otherUsrID));
        switch (client::RecvInt())
        {
        case 0:
            cout << "撤销管理员成功\n";
            sleep(1);
            return;
            break;
        case 1:
            cout << "无此群员\n";
            break;
        case 2:
            cout << "该成员并非管理员\n";
            break;
        default:
            cout << "啊？" << endl;
            break;
        }
        cout << "1.重新输入\n0.返回\n";
        choice = Get_Int();
        if (!choice)
            return;
    }
}

int Check_Authority_Ser(int GID)
{
    client::Send(From_Grp(Check_Authority, client::ID, GID));
    return client::RecvInt();
}

set<Message, MessageComparator> Get_Grp_ManageList_Ser(int GID)
{
    client::Send(From_Grp_Only(Get_Grp_ManageList, GID));
    return From_Json_Manage_List(To_Manage(client::Recv()));
}

void Manage_Apply_Ser(int ID, set<Message, MessageComparator> manage)
{
    int num;
    int choice;
    for (auto &m : manage)
    {
        system("clear");
        m.toString();
        cout << "1.同意\n0.拒绝\n";
        num = Get_Int();
        client::Send(From_Manage(m.event + 1, ID, m.SendID, num)); // 也可以加上处理用户的信息
        sigaction(SIGIO, &client::respond, 0);
        cout << "1.继续处理\n0.返回\n";
        choice = Get_Int();
        if (!choice)
            break;
    }
}

bool Quit_Ser(int GID)
{
    int num;
    while (1)
    {
        system("clear");
        cout << "1.确认\n0.后悔\n";
        num = Get_Int();
        if (num != 1 && num != 0)
        {
            continue;
        }
        if (!num)
            return num;
        client::Send(From_Grp(Quit_Grp, client::ID, GID));
        if (client::RecvInt())
            return 1;
        else
        {
            cout << "不能没有群主啊" << endl;
            sleep(1);
            return 0;
        }
    }
}

void Send_Msg_Grp_Ser(int GID)
{
    system("clear");
    cout << "群聊界面\n";
    int num;
    int choice;
    client::grpID = GID;
    client::Send(From_Grp(Get_grpChat, client::ID, GID));
    From_Json_Chat(client::Recv());
    string str;
    while (1)
    {
        cin >> str;
        if (str == "\\q")
        {
            client::grpID = -1;
            return;
        }
        cout << "\033[1A\x1b[2K\r";
        Message msg(Sendmsg_Togrp, client::ID, client::account, GID, str, gettime());
        msg.toString();
        client::Send(To_Json_Msg(msg)); //
        sigaction(SIGIO, &client::respond, 0);
    }
}

void Del_Member_Ser(int GID)
{

    system("clear");
    int otherUsrID;
    int choice;
    if (Check_Authority_Ser(GID) == 0)
    {
        cout << "你什么身份！？\n";
        sleep(1);
        return;
    }
    while (1)
    {
        system("clear");
        cout << "对方ID:";
        otherUsrID = Get_Int();
        if (otherUsrID == client::ID)
        {
            cout << "把计算机放入垃圾桶是吧你\n";
            cout << "1.重新输入\n0.返回\n";
            choice = Get_Int();
            if (!choice)
                return;
            else
                continue;
        }
        client::Send(From_Grp_Usr(Del_Member, client::ID, GID, otherUsrID));
        switch (client::RecvInt())
        {
        case 0:
            cout << "移除成功\n";
            sleep(1);
            return;
            break;
        case 1:
            cout << "无此群员\n";
            break;
        case 2:
            cout << "越位了昂\n";
            break;
        default:
            cout << "啊？" << endl;
            break;
        }
        cout << "1.重新输入\n0.返回\n";
        choice = Get_Int();
        if (!choice)
            return;
    }
}

bool Dissolve_Ser(int GID)
{
    int num;
    while (1)
    {
        system("clear");
        cout << "1.确认\n0.后悔\n";
        num = Get_Int();
        if (num != 1 && num != 0)
        {
            continue;
        }
        if (!num)
            return num;
        client::Send(From_Grp(Dissolve_Grp, client::ID, GID));
        if (client::RecvInt())
            return 1;
        else
        {
            cout << "我寻思你也不是群主啊" << endl;
            sleep(1);
            return 0;
        }
    }
}