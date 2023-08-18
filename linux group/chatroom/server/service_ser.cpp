#include "service_ser.hpp"
#include "../Serialization.hpp"
#include "database.hpp"
#include "../Message.hpp"
#include "../event.hpp"
#include "server.hpp"
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/ioctl.h>
#include <iostream>
using std::string, std::cout, std::cin, std::endl;

void Getfd(int *sfd)
{
    char buf[65536] = {};
    char *buff;
    bool set = 1;
    string jso = Recv(*sfd);
    string account, password, otherUsr_account, grp_account, filename, filehash;
    size_t size, this_size, offset = 0, this_offset = 0;
    int ID, otherUsrID, chatID, num, grpID, flags, n;
    int fd;
    UserTotal usr, opposite_usr;
    File file;
    Message msg;
    Group grp;
    struct stat s;
    // cout << "得到事件：" << endl;
    // cout << jso << endl;
    // cout << getopt(jso) << endl;
    switch (getopt(jso))
    {

    case Register:
        // 判断是否重名
        Get_Info(jso, nullptr, &account, &password, nullptr, nullptr, nullptr, nullptr);
        if (Database::User_Exist_Account(account))
        {
            SendInt(*sfd, 0);
            break;
        }
        usr = New_User(account, password);
        cout << "账号" << usr.ID << "注册\n";
        SendInt(*sfd, usr.ID);
        Database::Set_Account_To_ID(usr.ID, account);
        Database::User_In(usr.ID, To_Json_User(usr));
        Send(*sfd, Get_Notice(Database::User_Out(usr.ID)), 0); // 理论上没有但不发客户端在堵塞
        server::ID_To_Fd.emplace(usr.ID, *sfd);
        break;
    case Login:
        Get_Info(jso, nullptr, &account, &password, nullptr, nullptr, nullptr, nullptr);

        if (!Database::User_Exist_Account(account))
        {
            SendInt(*sfd, 0); // 不存在
            break;
        }
        usr = From_Json_UserTotal(Database::User_Out(Database::Get_Account_To_ID(account)));

        if (server::ID_To_Fd.find(usr.ID) != server::ID_To_Fd.end())
        {
            SendInt(*sfd, -1);
            break;
        }
        if (usr.password == password)
        {
            cout << "账号" << usr.ID << "登录\n";
            SendInt(*sfd, usr.ID);
            server::ID_To_Fd.emplace(usr.ID, *sfd);
            Send(*sfd, Get_Notice(Database::User_Out(usr.ID)), 0);
            Database::User_In(usr.ID, Notice_Clear(Database::User_Out(usr.ID)));
        }
        else
            SendInt(*sfd, 0); // 密码错误

        break;

    case User:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr); //
        Send(*sfd, To_UserBase(Database::User_Out(ID)), 0);
        break;

    case Frd_List:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        Send(*sfd, To_Json_Frdlist(usr), 0);
        cout << "返回用户" << ID << "好友信息\n";
        break;

    case Get_Frd_ManageList:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        Send(*sfd, Get_Manage(Database::User_Out(ID)), 0);
        cout << "返回用户" << ID << "待处理信息\n";
        break;

    case Exit:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        server::ID_To_Fd.erase(ID); // 在server里再关一次
        cout << "用户" << ID << "退出\n";
        break;

    case Send_Add_Frd:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        if (!Database::User_Exist_ID(otherUsrID))
        {
            SendInt(*sfd, 1);
            break;
        }

        // 检查是否找到了这个值
        if (usr.frd.find(otherUsrID) != usr.frd.end())
        {
            SendInt(*sfd, 2);
            break;
        }
        SendInt(*sfd, 0);
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
            SendInt(*sfd, 1);
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
        SendInt(*sfd, 0);
        break;

    case Block_Frd:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        // 检查是否找到了这个值
        if (usr.frd.find(otherUsrID) == usr.frd.end())
        {
            SendInt(*sfd, 1);
            break;
        }
        usr.frd_Block[otherUsrID] = !usr.frd_Block[otherUsrID];
        Database::User_In(ID, To_Json_User(usr));
        SendInt(*sfd, 0);
        break;

    case Search_Frd:
        Get_Info(jso, nullptr, nullptr, nullptr, nullptr, &otherUsr_account, nullptr, nullptr); //
        if (Database::User_Exist_Account(otherUsr_account))
            SendInt(*sfd, Database::Get_Account_To_ID(otherUsr_account));
        else
            SendInt(*sfd, 0);
        break;

    case Able_To_Send_Frd:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        // 检查是否找到了这个值
        if (usr.frd.find(otherUsrID) != usr.frd.end())
        {
            if (usr.frd_Block[otherUsrID])
            {
                SendInt(*sfd, 1);
                break;
            }
            opposite_usr = From_Json_UserTotal(Database::User_Out(otherUsrID));
            if (opposite_usr.frd_Block[ID])
            {
                SendInt(*sfd, 2);
                break;
            }
            SendInt(*sfd, 0);
            cout << "好友" << otherUsrID << "可發送" << endl;
            break;
        }
        SendInt(*sfd, 3);
        cout << "非好友" << otherUsrID << endl;
        break;

    case Get_frdChat:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        Send(*sfd, Database::Chat_Out(usr.frd[otherUsrID]), 0); // 固定条数
        cout << "返回" << ID << "和" << otherUsrID << "的聊天记录" << endl;
        break;

    case Sendfile:
    {
        epoll_ctl(server::epfd, EPOLL_CTL_DEL, *sfd, nullptr);

        auto it = find_if(server::ID_To_Fd.begin(), server::ID_To_Fd.end(),
                          [&sfd](const pair<int, int> &p)
                          { return p.second == *sfd; });
        if (it != server::ID_To_Fd.end())
        {
            server::ID_To_Fd.erase(it);
        }

        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, nullptr, nullptr);
        Get_Fileinfo(jso, &filename, &size, &filehash);
        usr = From_Json_UserTotal(Database::User_Out(ID));
        opposite_usr = From_Json_UserTotal(Database::User_Out(otherUsrID));
        file = File(ID, usr.account, filename, size, filehash);

        // if (!Database::File_Exist(filehash)) // 其实可以直接检测文件对吧
        // {
        //     Database::File_In(filehash, 0);
        //     offset = 0;
        //     SendInt(*sfd, 0);
        //     fd = open(filehash.c_str(), O_WRONLY | O_CREAT, 0660); //| O_EXCL
        // }
        // else
        // {
        //     offset = Database::File_Out(filehash);
        // SendInt(*sfd, offset);
        //     if (offset == size)
        //     {
        //         opposite_usr.file.emplace_back(file);
        //         Database::User_In(otherUsrID, To_Json_User(opposite_usr));
        //         msg = Message(Sendfile, ID, usr.account, otherUsrID, gettime());
        //         Relay_To_User(otherUsrID, msg);
        //         break;
        //     }
        //     fd = open(filehash.c_str(), O_WRONLY | O_APPEND, 0660);
        // }
        string path = "file/";
        string real_path = path + filehash; //
        if (stat(real_path.c_str(), &s) == -1)
        {
            offset = 0;
            SendInt(*sfd, 0);
            fd = open(real_path.c_str(), O_WRONLY | O_CREAT, 0660); //| O_EXCL
        }
        else
        {
            offset = s.st_size;
            SendInt(*sfd, offset);
            if (offset == size)
            {
                epoll_ctl(server::epfd, EPOLL_CTL_ADD, *sfd, &server::evadd);
                opposite_usr.file.emplace_back(file);
                Database::User_In(otherUsrID, To_Json_User(opposite_usr));
                msg = Message(Sendfile, ID, usr.account, otherUsrID, gettime());
                Relay_To_User(otherUsrID, msg);
                cout << "接收完成" << endl;
                return;
            }
            fd = open(real_path.c_str(), O_WRONLY | O_APPEND, 0660);
        }

        this_size = size - offset;
        buff = new char[this_size];
        this_offset = 0;

        while (this_offset < this_size)
        {
            int received = recv(*sfd, buff + this_offset, this_size, 0);
            if (received == 0)
            {
                // 发生错误或连接关闭
                cout << "连接断开" << endl;
                break;
            }
            if (received == -1 && (errno == (EAGAIN | EWOULDBLOCK))) //?   && set
            {
                // if (!set)
                //     break;
                // cout << "啊？" << endl;
                continue;
            }
            // set = 0; //?
            this_offset += received;
            cout << this_offset << endl;
        }
        this_offset = write(fd, buff, this_offset);
        offset += this_offset;
        // while (offset < size)
        // {
        //     memset(buf, 0, sizeof(buf));
        //     n = recv(*sfd, buf, sizeof(buf), 0);
        //     if (n == 0)
        //     {
        //         // 发生错误或连接关闭
        //         cout << "连接断开" << endl;
        //         break;
        //     }
        //     if (n == -1 && (errno == (EAGAIN | EWOULDBLOCK)) && set) // 读几次就读不到了，就卡在这了
        //     {
        //         cout << "啊?" << endl;
        //         continue;
        //     }
        //     if (n == -1)
        //     {
        //         cout << "发生错误" << endl;
        //         break;
        //     }
        //     set = 0;
        //     offset += write(fd, buf, n);
        //     cout << offset << endl;
        // }
        close(fd);
        // chmod(filehash.c_str(), 0660);
        delete[] buff;
        cout << offset << endl;

        epoll_ctl(server::epfd, EPOLL_CTL_ADD, *sfd, &server::evadd);

        SendInt(*sfd, offset);

        server::ID_To_Fd.emplace(usr.ID, *sfd);

        if (offset == size)
        {
            opposite_usr.file.emplace_back(file);
            Database::User_In(otherUsrID, To_Json_User(opposite_usr));
            msg = Message(Sendfile, ID, usr.account, otherUsrID, gettime());
            Relay_To_User(otherUsrID, msg);
            break;
        }
        break;
    }
    case File_List:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr); //
        Send(*sfd, Get_File(Database::User_Out(ID)), 0);
        cout << "返回用户" << ID << "文件信息\n";
        break;

    case Recvfile:
    {
        auto it = find_if(server::ID_To_Fd.begin(), server::ID_To_Fd.end(),
                          [&sfd](const pair<int, int> &p)
                          { return p.second == *sfd; });
        if (it != server::ID_To_Fd.end())
        {
            server::ID_To_Fd.erase(it);
        }

        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
        num = Get_Num(jso);
        off_t offset = Get_Offset(jso);
        usr = From_Json_UserTotal(Database::User_Out(ID));
        auto i = std::next(usr.file.begin(), num);
        file = *i;

        string path = "file/";
        string real_path = path + file.filehash; //
        int fd = open(real_path.c_str(), O_RDONLY);
        while (offset < file.size)
            cout << sendfile(*sfd, fd, &offset, file.size) << endl;
        if (offset == file.size)
        {
            cout << "发送成功" << endl;

            msg = Message(Recvfile, ID, usr.account, file.sendID, gettime());
            Relay_To_User(file.sendID, msg);
        }
        else
            cout << "发送失败" << endl;
        close(fd);

        server::ID_To_Fd.emplace(usr.ID, *sfd);
    }

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
        Send(*sfd, To_Json_Grplist(usr.grp), 0);
        cout << "返回用户" << ID << "群组信息\n";
        break;

    case New_Grp:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, nullptr, &grp_account);
        usr = From_Json_UserTotal(Database::User_Out(ID));

        if (Database::Grp_Exist_name(grp_account))
        {
            SendInt(*sfd, 0);
            break;
        }
        chatID = Database::Get_ChatID();
        grp = Group(chatID, grp_account);
        grp.mem.emplace(ID, 2);
        cout << "新建" << grp.GID << "群聊\n";
        SendInt(*sfd, 1);
        Database::Set_Name_To_GID(grp.GID, grp_account);
        Database::Grp_In(grp.GID, To_Json_Grp(grp));
        usr.grp.emplace(grp.GID, chatID);
        Database::User_In(ID, To_Json_User(usr));
        break;

    case Choose_Grp:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr);
        usr = From_Json_UserTotal(Database::User_Out(ID));
        if (usr.grp.find(grpID) != usr.grp.end())
            SendInt(*sfd, 1);
        else
            SendInt(*sfd, 0);
        break;

    case Grp_Member_List:
        Get_Info(jso, nullptr, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr); //
        grp = From_Json_Grp(Database::Grp_Out(grpID));
        Send(*sfd, To_Json_Grp_Member_List(grp.mem), 0);
        cout << "返回群组" << grpID << "成员信息\n";
        break;

    case Check_Authority:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr); //
        grp = From_Json_Grp(Database::Grp_Out(grpID));
        SendInt(*sfd, grp.mem[ID]);
        break;

    case Get_Grp_ManageList:
        Get_Info(jso, nullptr, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr);
        Send(*sfd, Get_Manage(Database::Grp_Out(grpID)), 0);
        cout << "返回群组" << grpID << "待处理信息\n";
        break;

    case Add_Manager:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, &grpID, nullptr); //
        grp = From_Json_Grp(Database::Grp_Out(grpID));
        if (grp.mem.find(otherUsrID) == grp.mem.end())
        {
            SendInt(*sfd, 1);
            break;
        }
        if (grp.mem[otherUsrID] == 1)
        {
            SendInt(*sfd, 2);
            break;
        }
        SendInt(*sfd, 0);
        cout << "添加" << otherUsrID << "为管理员\n";
        msg = Message(Add_Manager, ID, "", grpID, gettime());
        msg.Receive_Account = grp.name;
        grp.mem[otherUsrID] = 1;
        Database::Grp_In(grpID, To_Json_Grp(grp));
        Relay_To_User(otherUsrID, msg);
        break;

    case Del_Manager:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, &grpID, nullptr); //
        grp = From_Json_Grp(Database::Grp_Out(grpID));
        if (grp.mem.find(otherUsrID) == grp.mem.end())
        {
            SendInt(*sfd, 1);
            break;
        }
        if (grp.mem[otherUsrID] == 0)
        {
            SendInt(*sfd, 2);
            break;
        }
        SendInt(*sfd, 0);
        cout << "去除" << otherUsrID << "的管理员\n";
        msg = Message(Del_Manager, ID, "", grpID, gettime());
        msg.Receive_Account = grp.name;
        grp.mem[otherUsrID] = 0;
        Database::Grp_In(grpID, To_Json_Grp(grp));
        Relay_To_User(otherUsrID, msg);
        break;

    case Send_Add_Grp:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr); //
        usr = From_Json_UserTotal(Database::User_Out(ID));
        if (!Database::Grp_Exist_ID(grpID))
        {
            SendInt(*sfd, 1);
            break;
        }

        // 检查是否找到了这个值
        if (usr.grp.find(grpID) != usr.grp.end())
        {
            SendInt(*sfd, 2);
            break;
        }
        SendInt(*sfd, 0);
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
            SendInt(*sfd, 0);
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
        SendInt(*sfd, 1);
        break;

    case Get_grpChat:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr);
        usr = From_Json_UserTotal(Database::User_Out(ID));
        Send(*sfd, Database::Chat_Out(usr.grp[grpID]), 0);
        cout << "返回群" << grpID << "的聊天记录" << endl;
        break;

    case Sendmsg_Togrp:
        msg = From_Json_Msg(jso);
        grp = From_Json_Grp(Database::Grp_Out(msg.ReceiveID));
        chatID = grp.ChatID;
        msg.Receive_Account = grp.name;
        // 发实时
        for (const auto &p : grp.mem)
        {
            if (p.first != msg.SendID)
            {
                Relay_To_User(p.first, msg);
            }
        }
        Database::Chat_In(chatID, Add_Msg(To_Json_Msg(msg), Database::Chat_Out(chatID)));
        cout << "追加" << msg.SendID << "发给群" << msg.ReceiveID << "的消息" << endl;
        break;

    case Del_Member:
        Get_Info(jso, &ID, nullptr, nullptr, &otherUsrID, nullptr, &grpID, nullptr);
        grp = From_Json_Grp(Database::Grp_Out(grpID));
        if (grp.mem.find(otherUsrID) == grp.mem.end())
        {
            SendInt(*sfd, 1);
            break;
        }
        if (grp.mem[otherUsrID] >= grp.mem[ID])
        {
            SendInt(*sfd, 2);
            break;
        }
        SendInt(*sfd, 0);
        cout << "移除用户" << otherUsrID << endl;
        msg = Message(Del_Member, ID, "", grpID, gettime());
        msg.Receive_Account = grp.name;
        grp.mem.erase(otherUsrID);
        opposite_usr = From_Json_UserTotal(Database::User_Out(otherUsrID));
        opposite_usr.grp.erase(grpID);
        Database::User_In(otherUsrID, To_Json_User(opposite_usr));
        Database::Grp_In(grpID, To_Json_Grp(grp));
        Relay_To_User(otherUsrID, msg);
        break;

    case Dissolve_Grp:
        Get_Info(jso, &ID, nullptr, nullptr, nullptr, nullptr, &grpID, nullptr);
        grp = From_Json_Grp(Database::Grp_Out(grpID));
        if (grp.mem[ID] != 2)
        {
            SendInt(*sfd, 0);
            break;
        }

        msg = Message(Dissolve_Grp, ID, usr.account, grpID, gettime());
        msg.Receive_Account = grp.name;
        cout << "群聊" << grpID << "解散" << endl;

        usr = From_Json_UserTotal(Database::User_Out(ID));
        grp.mem.erase(ID);
        usr.grp.erase(grpID);
        Database::User_In(ID, To_Json_User(usr));
        for (const auto &p : grp.mem)
        {
            usr = From_Json_UserTotal(Database::User_Out(p.first));
            usr.grp.erase(grpID);
            Database::User_In(p.first, To_Json_User(usr));
            Relay_To_User(p.first, msg);
        }
        Database::Del_Chat(grp.ChatID);
        Database::Del_Grp(grpID);
        Database::Del_GrpName(grp.name);
        SendInt(*sfd, 1);
        break;

    default: // jump to case label???
        cout << "啊？" << endl;
        break;
    }
    // close(*sfd);
}

void Send(int sfd, string jso, bool type)
{
    string realjso = Set_Type(jso, type);
    // 在这里用json设定是实时信息还是回应，多传一个参数
    int numRead = realjso.length();
    char *buffer = new char[numRead + 4];
    // cout << realjso << endl;
    memcpy(buffer, &numRead, sizeof(int));
    memcpy(buffer + 4, realjso.c_str(), numRead);
    send(sfd, buffer, numRead + 4, 0);
    // cout << send(sfd, buffer, numRead + 4, 0) << endl;
}

void SendInt(int sfd, long long num) //,bool flag
{
    Send(sfd, Set_Num(num), 0);
}

string Recv(int sfd)
{
    int reqLen = 0;
    recv(sfd, (void *)&reqLen, sizeof(int), 0);

    char *buffer = new char[reqLen];
    recv(sfd, buffer, reqLen, 0);
    string ans(buffer, reqLen);
    delete[] buffer;
    return ans;
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
