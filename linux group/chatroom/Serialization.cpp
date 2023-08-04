#include <iostream>
#include <json.hpp>
#include "Serialization.hpp"
#include "user.hpp"
#include "Message.hpp"
#include "server/database.hpp"
#include "client/client.hpp"
using std::string, std::cout, std::endl, nlohmann::json;

string Get_Type(string jso)
{
    json j = json::parse(jso);
    if (j["type"]) // 在线消息
    {
        // 接受message输出
        Message msg = From_Json_Msg(jso);
        msg.toString();
        return client::Recv();
    }
    else
        return jso; // 回应
}

int Get_Num(string jso)
{
    json j = json::parse(jso);
    return j["num"]; // 回应
}

string From_Main(int opt, string account, string password)
{
    json j = {
        {"event", opt},
        {"account", account},
        {"password", password}};
    return j.dump();
}

string From_Self(int opt, int ID)
{
    json j = {
        {"event", opt},
        {"ID", ID}};

    return j.dump();
}

string From_Manage(int opt, int ID, int oppositeID, int num)
{
    json j = {
        {"event", opt},
        {"ID", ID},
        {"oppositeID", oppositeID},
        {"num", num}};

    return j.dump();
}

void From_Json_Frdlist(string jso)
{
    json frd_arr = json::parse(jso);
    unordered_map<int, bool> block = frd_arr["frd_block"];
    for (const auto &f : frd_arr["frd"])
    {
        UserBase f_user(f["ID"], f["account"], f["islogin"]);
        f_user.toString();
        if (block[f["ID"]])
            cout << "屏蔽\n";
        else
            cout << "畅通\n";
        cout << "==================================================\n";
    }
    if (frd_arr["frd"].empty())
        cout << "当前无好友" << endl;
}

string From_Frd(int opt, int ID, int oppositeID)
{
    json j = {
        {"event", opt},
        {"ID", ID},
        {"oppositeID", oppositeID}};
    return j.dump();
}

string From_Frd_Account(int opt, string opposite_account)
{
    json j = {
        {"event", opt},
        {"opposite_account", opposite_account}};
    return j.dump();
}

void From_Json_Chat(string jso)
{
    json list = json::parse(jso);
    for (const auto &j : list["chat"])
    {
        Message msg(j["event"], j["sendID"], j["send_account"], j["receiveID"], j["receiveID_account"], j["str"], j["time"], j["num"]);
        msg.toString();
    }
}

/*














*/
json To_Json_MsgList(list<Message> qu)
{
    json que;
    for (const auto &q : qu)
    {
        json j = json::parse(To_Json_Msg(q));
        que.push_back(j);
    }
    return que;
}

string To_Json_User(UserTotal usr)
{
    json frd_map(usr.frd);
    json grp_map(usr.grp);
    json block(usr.frd_Block);
    json notice = To_Json_MsgList(usr.notice);
    json manage = To_Json_MsgList(usr.manage);
    json j = {
        {"ID", usr.ID},
        {"account", usr.account},
        {"password", usr.password},
        {"islogin", usr.islogin},
        {"frd", frd_map},
        {"frd_block", block},
        {"grp", grp_map},
        {"notice", notice},
        {"manage", manage}};
    return j.dump();
}

string Get_Notice(string jso)
{
    json j = json::parse(jso);
    json n;
    n["notice"] = j["notice"];
    return n.dump();
}

json To_Notice(string jso)
{
    json j = json::parse(jso);
    return j["notice"];
}

string Notice_Clear(string jso)
{
    json j = json::parse(jso), n;
    j["notice"] = n;
    return j.dump();
}

string Get_Manage(string jso)
{
    json j = json::parse(jso);
    json n;
    n["manage"] = j["manage"];
    return n.dump();
}

json To_Manage(string jso)
{
    json j = json::parse(jso);
    return j["manage"];
}

list<Message> From_Json_MsgList(json j)
{
    list<Message> li;
    for (const auto &l : j)
    {
        Message msg(l["event"], l["sendID"], l["send_account"], l["receiveID"], l["receiveID_account"], l["str"], l["time"], l["num"]);
        li.push_back(msg);
    }
    return li;
}

UserTotal From_Json_UserTotal(string jso)
{
    json j = json::parse(jso);
    list<Message> notice = From_Json_MsgList(j["notice"]);
    list<Message> manage = From_Json_MsgList(j["manage"]);
    return UserTotal(UserBase(j.at("ID"), j["account"], j["password"], j["islogin"]), j["frd"], j["frd_block"], j["grp"], notice, manage);
}

UserBase From_Json_UserBase(string jso)
{
    json j = json::parse(jso);
    return UserBase(j.at("ID"), j["account"], j["islogin"]); // 构造
}

/*









*/
Event getopt(const string &jso)
{
    json j = json::parse(jso);
    return j.at("event");
}

string Set_Type(string jso, bool type)
{
    json j = json::parse(jso);
    j["type"] = type;
    return j.dump();
}

string Set_Num(int num)
{
    json j{
        {"num", num}};
    return j.dump();
}

void Get_Info(const string &jso, int *ID, string *account, string *password, int *oppositeID, string *opposite_account)
{
    json j = json::parse(jso);
    if (ID != nullptr)
        *ID = j.at("ID");
    if (account != nullptr)
        *account = j.at("account");
    if (password != nullptr)
        *password = j.at("password");
    if (oppositeID != nullptr)
        *oppositeID = j.at("oppositeID");
    if (opposite_account != nullptr)
        *opposite_account = j.at("opposite_account");
}

string To_UserBase(string jso)
{
    json total = json::parse(jso);
    json base{
        {"ID", total["ID"]},
        {"account", total["account"]},
        {"islogin", total["islogin"]},
    };
    return base.dump();
}

string Change_isLogin(string jso)
{
    json j = json::parse(jso);
    bool flag = j["islogin"];
    // flag = ~flag;有问题
    flag = !flag;
    j["islogin"] = flag;
    return j.dump();
}

string Add_Friend(int ID, string jso, int chatID)
{
    json j = json::parse(jso);
    j["frd"].push_back({ID, chatID}); //[]
    j["frd_block"].push_back({ID, false});
    return j.dump();
}

string Add_Notice(string jso, Message msg)
{
    json j = json::parse(jso);
    json m = json::parse(To_Json_Msg(msg));
    j["notice"].push_back(m);
    return j.dump();
}

string Add_Manage(string jso, Message msg)
{
    json j = json::parse(jso);
    json m = json::parse(To_Json_Msg(msg));
    j["manage"].push_back(m);
    return j.dump();
}

string Del_Manage(string jso)
{
    json j = json::parse(jso);
    j["manage"].erase(0);
    return j.dump();
}

Message From_Json_Msg(string jso)
{
    json j = json::parse(jso);
    return Message(j["event"], j["sendID"], j["send_account"], j["receiveID"], j["receiveID_account"], j["str"], j["time"], j["num"]);
}

string To_Json_Msg(Message msg)
{
    json j;
    j["event"] = msg.event;
    j["sendID"] = msg.SendID;
    j["send_account"] = msg.Send_Account;
    j["receiveID"] = msg.ReceiveID;
    j["receiveID_account"] = msg.Receive_Account;
    j["str"] = msg.Str;
    j["time"] = msg.Time;
    j["num"] = msg.num;
    return j.dump();
}

string Add_Msg(string msg, string chat)
{
    json Msg = json::parse(msg), Chat = json::parse(chat);
    Chat["chat"].push_back(Msg);
    return Chat.dump();
}

string To_Json_Frdlist(const UserTotal usr)
{
    json j, frd, f;
    for (const auto &FID : usr.frd) // std::pair<int, int>
    {
        f = json::parse(To_UserBase(Database::User_Out(FID.first)));
        frd.push_back(f);
    }
    j["frd"] = frd;
    j["frd_block"] = usr.frd_Block;
    return j.dump();
}