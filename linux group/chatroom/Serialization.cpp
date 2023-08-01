#include <iostream>
#include <json.hpp>
#include "Serialization.hpp"
#include "server/database.hpp"
#include "user.hpp"
#include "client/client.hpp"
using std::string, std::cout, std::endl, nlohmann::json;

string Get_Type(string jso)
{
    json j = json::parse(jso);
    if (j["type"]) // 在线消息
    {
        // 接受message输出
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
        {"option", opt},
        {"account", account},
        {"password", password}};
    return j.dump();
}

string From_Self(int opt, int ID)
{
    json j = {
        {"option", opt},
        {"ID", ID}};

    return j.dump();
}

list<UserBase> From_Json_Frdlist(string jso)
{
    list<UserBase> frd;
    json frd_arr = json::parse(jso);
    for (const auto &f : frd_arr["frd"])
    {
        UserBase f_user(f["ID"], f["account"], f["islogin"]);
        frd.push_back(f_user);
    }
    return frd;
}

string From_Frd(int opt, int ID, int oppositeID)
{
    json j = {
        {"option", opt},
        {"ID", ID},
        {"oppositeID", oppositeID}};
    return j.dump();
}

string From_Frd_Account(int opt, string opposite_account)
{
    json j = {
        {"option", opt},
        {"opposite_account", opposite_account}};
    return j.dump();
}

/*














*/

string To_Json_User(UserTotal usr)
{
    json frd_map(usr.frd);
    json grp_map(usr.grp);
    json j = {
        {"ID", usr.ID},
        {"account", usr.account},
        {"password", usr.password},
        {"islogin", usr.islogin},
        {"frd", frd_map},
        {"grp", grp_map}};
    return j.dump();
}

UserTotal From_Json_UserTotal(string jso)
{
    json j = json::parse(jso);
    return UserTotal(UserBase(j.at("ID"), j["account"], j["password"], j["islogin"]), j["frd"], j["grp"]); //
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
    return j.at("option");
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
    j["frd"].push_back({ID, chatID});
    return j.dump();
}

string To_Json_Frdlist(const unordered_map<int, int> &frd)
{
    json j, frd;
    for (const auto &FID : frd) // std::pair<int, int>
    {
        json f = json::parse(To_UserBase(Database::User_Out(FID.first)));
        frd.push_back(f);
    }
    j["frd"] = frd;
    return j.dump();
}