#include "service_ser.hpp"
#include "../Serialization.hpp"
#include "database.hpp"
#include "../Message.hpp"
#include "../event.hpp"
#include "server.hpp"
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
using std::string, std::cout, std::cin, std::endl;

void Getfd(int *fd)
{
    string jso = Recv(*fd);
    string account, password, otherUsr_account, grp_account;
    int ID, otherUsrID, chatID, num, grpID;
    UserTotal usr, opposite_usr;
    Message msg;
    Group grp;
    // cout << "得到事件：" << getopt(jso) << endl;
    switch (getopt(jso))
    {

    case Register:
        // 判断是否重名
        Get_Info(jso, nullptr, &account, &password, nullptr, nullptr, nullptr, nullptr);
        if (Database::User_Exist_Account(account))
        {
            SendInt(*fd, 0);
            break;
        }
        usr = New_User(account, password);
        cout << "账号" << usr.ID << "注册\n";
        SendInt(*fd, usr.ID);
        Database::Set_Account_To_ID(usr.ID, account);
        Database::User_In(usr.ID, To_Json_User(usr));
        Send(*fd, Get_Notice(Database::User_Out(usr.ID)), 0); // 理论上没有但不发客户端在堵塞
        server::ID_To_Fd.emplace(usr.ID, *fd);
        break;
    case Login:
        Get_Info(jso, nullptr, &account, &password, nullptr, nullptr, nullptr, nullptr);

        if (!Database::User_Exist_Account(account))
        {
            SendInt(*fd, 0); // 不存在
            break;
        }
        usr = From_Json_UserTotal(Database::User_Out(Database::Get_Account_To_ID(account)));
        if (usr.password == password)
        {
            cout << "账号" << usr.ID << "登录\n";
            Change_isLogin_Ser(usr.ID);
            SendInt(*fd, usr.ID);
            server::ID_To_Fd.emplace(usr.ID, *fd);
            Send(*fd, Get_Notice(Database::User_Out(usr.ID)), 0);
            Database::User_In(usr.ID, Notice_Clear(Database::User_Out(usr.ID)));
        }
        else
            SendInt(*fd, 0); // 密码错误

        break;

    case User:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr); //
        Send(*fd, To_UserBase(Database::User_Out(ID)), 0);
        break;

    case Frd_List:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        Send(*fd, To_Json_Frdlist(usr), 0);
        cout << "返回用户" << ID << "好友信息\n";
        break;

    case Get_Frd_ManageList:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        Send(*fd, Get_Manage(Database::User_Out(ID)), 0);
        cout << "返回用户" << ID << "待处理信息\n";
        break;

    case Exit:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        Change_isLogin_Ser(ID);
        server::ID_To_Fd.erase(ID); // 在server里再关一次
        cout << "用户" << ID << "退出\n";
        break;

    case Send_Add_Frd:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        if (!Database::User_Exist_ID(otherUsrID))
        {
            SendInt(*fd, 1);
            break;
        }

        // 检查是否找到了这个值
        if (usr.frd.find(otherUsrID) != usr.frd.end())
        {
            SendInt(*fd, 2);
            break;
        }
        SendInt(*fd, 0);
        msg = Message(Send_Add_Frd, ID, usr.account, otherUsrID, gettime());
        Database::User_In(otherUsrID, Add_Manage(Database::User_Out(otherUsrID), msg));
        Relay_To_User(otherUsrID, msg);

        break;

    case Recv_Add_Frd:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr);
        usr = From_Json_UserTotal(Database::User_Out(ID));
        usr.manage.erase(usr.manage.begin());
        cout << "返回用户" << ID << "处理信息\n";
        if (Get_Num(jso))
        {
            chatID = Database::Get_ChatID();
            usr.frd.emplace(otherUsrID, chatID);
            usr.frd_Block.emplace(otherUsrID, 0);
            Database::User_In(otherUsrID, Add_Friend(ID, Database::User_Out(otherUsrID), chatID));
            Relay_To_User(otherUsrID, Message(Recv_Add_Frd, ID, usr.account, otherUsrID, gettime(), 1));
        }
        else
        {
            Relay_To_User(otherUsrID, Message(Recv_Add_Frd, ID, usr.account, otherUsrID, gettime(), 0));
        }
        Database::User_In(ID, To_Json_User(usr));

        break;

    case Del_Frd:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        // 检查是否找到了这个值
        if (usr.frd.find(otherUsrID) == usr.frd.end())
        {
            SendInt(*fd, 1);
            break;
        }
        // 发送消息
        Relay_To_User(otherUsrID, Message(Del_Frd, ID, usr.account, otherUsrID, gettime(), 0));
        Database::Del_Chat(usr.frd[otherUsrID]); // 构造了删
        usr.frd.erase(otherUsrID);
        usr.frd_Block.erase(otherUsrID);
        Database::User_In(ID, To_Json_User(usr));
        { //
            UserTotal opposite = From_Json_UserTotal(Database::User_Out(otherUsrID));
            opposite.frd.erase(ID);
            opposite.frd_Block.erase(ID);
            Database::User_In(otherUsrID, To_Json_User(opposite));
        }
        SendInt(*fd, 0);
        break;

    case Block_Frd:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        // 检查是否找到了这个值
        if (usr.frd.find(otherUsrID) == usr.frd.end())
        {
            SendInt(*fd, 1);
            break;
        }
        usr.frd_Block[otherUsrID] = !usr.frd_Block[otherUsrID];
        Database::User_In(ID, To_Json_User(usr));
        SendInt(*fd, 0);
        break;

    case Search_Frd:
        Get_Info(jso, nullptr, nullptr, nullptr, nullptr, &otherUsr_account, nullptr, nullptr); //
        if (Database::User_Exist_Account(otherUsr_account))
            SendInt(*fd, Database::Get_Account_To_ID(otherUsr_account));
        else
            SendInt(*fd, 0);
        break;

    case Able_To_Send_Frd:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        opposite_usr = From_Json_UserTotal(Database::User_Out(otherUsrID));
        // 检查是否找到了这个值
        if (usr.frd.find(otherUsrID) != usr.frd.end())
        {
            if (usr.frd_Block[otherUsrID])
            {
                SendInt(*fd, 1);
                break;
            }
            if (opposite_usr.frd_Block[ID])
            {
                SendInt(*fd, 2);
                break;
            }
            SendInt(*fd, 0);
            cout << "好友" << otherUsrID << "可發送" << endl;
            break;
        }
        SendInt(*fd, 3);
        break;

    case Get_frdChat:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        Send(*fd, Database::Chat_Out(usr.frd[otherUsrID]), 0);
        cout << "返回" << ID << "和" << otherUsrID << "的聊天记录" << endl;
        break;

    case Sendmsg_Tofrd:
        msg = From_Json_Msg(jso);
        usr = From_Json_UserTotal(Database::User_Out(msg.SendID));
        chatID = usr.frd[msg.ReceiveID];
        // 发实时
        Relay_To_User(msg.ReceiveID, msg);
        Database::Chat_In(chatID, Add_Msg(To_Json_Msg(msg), Database::Chat_Out(chatID)));
        cout << "追加" << msg.SendID << "发给" << msg.ReceiveID << "的消息" << endl;
        break;

    case Grp_List:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        Send(*fd, To_Json_Grplist(usr.grp), 0);
        cout << "返回用户" << ID << "群组信息\n";
        break;

    case New_Grp:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, &grp_account);
        usr = From_Json_UserTotal(Database::User_Out(ID));

        if (Database::Grp_Exist_name(grp_account))
        {
            SendInt(*fd, 0);
            break;
        }
        chatID = Database::Get_ChatID();
        grp = Group(chatID, grp_account);
        grp.mem.emplace(ID, 2);
        cout << "新建" << grp.GID << "群聊\n";
        SendInt(*fd, 1);
        Database::Set_Name_To_GID(grp.GID, grp_account);
        Database::Grp_In(grp.GID, To_Json_Grp(grp));
        usr.grp.emplace(grp.GID, chatID);
        Database::User_In(ID, To_Json_User(usr));
        break;

    case Choose_Grp:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr);
        usr = From_Json_UserTotal(Database::User_Out(ID));
        if (usr.grp.find(grpID) != usr.grp.end())
            SendInt(*fd, 1);
        else
            SendInt(*fd, 0);
        break;

    case Grp_Member_List:
        Get_Info(jso, nullptr, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr); //
        grp = From_Json_Grp(Database::Grp_Out(grpID));
        Send(*fd, To_Json_Grp_Member_List(grp.mem), 0);
        cout << "返回群组" << grpID << "成员信息\n";
        break;

    case Get_Grp_ManageList:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        Send(*fd, Get_Manage(Database::Grp_Out(ID)), 0);
        cout << "返回群组" << ID << "待处理信息\n";
        break;

    case Send_Add_Grp:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        if (!Database::Grp_Exist_ID(grpID))
        {
            SendInt(*fd, 1);
            break;
        }

        // 检查是否找到了这个值
        if (usr.grp.find(grpID) != usr.grp.end())
        {
            SendInt(*fd, 2);
            break;
        }
        SendInt(*fd, 0);
        cout << "用户" << ID << "发送加群申请\n";
        grp = From_Json_Grp(Database::Grp_Out(grpID));
        msg = Message(Send_Add_Grp, ID, usr.account, grpID, gettime());
        msg.Receive_Account = grp.name;
        grp.manage.emplace(msg);
        Database::Grp_In(grpID, To_Json_Grp(grp));
        for (const auto &p : grp.mem)
        {
            if (p.second != 0)
            {
                Relay_To_User(p.first, msg);
            }
        }

        break;

    case Recv_Add_Grp:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr);
        grp = From_Json_Grp(Database::Grp_Out(ID));
        grp.manage.erase(grp.manage.begin());
        cout << "返回组" << ID << "处理信息\n";
        if (Get_Num(jso))
        {
            opposite_usr = From_Json_UserTotal(Database::User_Out(otherUsrID));
            opposite_usr.grp.emplace(grp.GID, grp.ChatID);
            grp.mem.emplace(otherUsrID, 0);
            Database::User_In(otherUsrID, To_Json_User(opposite_usr));
            Relay_To_User(otherUsrID, Message(Recv_Add_Grp, ID, grp.name, otherUsrID, gettime(), 1));
        }
        else
        {
            Relay_To_User(otherUsrID, Message(Recv_Add_Grp, ID, grp.name, otherUsrID, gettime(), 0));
        }
        Database::Grp_In(ID, To_Json_Grp(grp));

        break;

    case Quit_Grp:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr);
        grp = From_Json_Grp(Database::Grp_Out(grpID));
        if (grp.mem[ID] == 2)
        {
            SendInt(*fd, 0);
            break;
        }
        usr = From_Json_UserTotal(Database::User_Out(ID));
        grp.mem.erase(ID);
        usr.grp.erase(grpID);
        Database::User_In(ID, To_Json_User(usr));
        Database::Grp_In(grpID, To_Json_Grp(grp));
        msg = Message(Quit_Grp, ID, usr.account, grpID, gettime());
        msg.Receive_Account = grp.name;
        cout << "用户" << ID << "退出群聊" << grpID << endl;
        for (const auto &p : grp.mem)
        {
            if (p.second != 0)
            {
                Relay_To_User(p.first, msg);
            }
        }
        SendInt(*fd, 1);

        break;

    default: // jump to case label???
        cout << "啊？" << endl;
        break;
    }
    // close(*fd);
}

void Send(int fd, string jso, bool type)
{
    string realjso = Set_Type(jso, type);
    // 在这里用json设定是实时信息还是回应，多传一个参数
    int numRead = realjso.length();
    char *buffer = new char[numRead + 4];
    // cout << realjso << endl;
    memcpy(buffer, &numRead, sizeof(int));
    memcpy(buffer + 4, realjso.c_str(), numRead);
    send(fd, buffer, numRead + 4, 0);
    // cout << send(fd, buffer, numRead + 4, 0) << endl;
}

void SendInt(int fd, int num) //,bool flag
{
    Send(fd, Set_Num(num), 0);
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

void Relay_To_User(int otherUsrID, Message msg)
{
    if (server::ID_To_Fd.find(otherUsrID) != server::ID_To_Fd.end())
        Send(server::ID_To_Fd[otherUsrID], To_Json_Msg(msg), 1);
    else
        Database::User_In(otherUsrID, Add_Notice(Database::User_Out(otherUsrID), msg));
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
