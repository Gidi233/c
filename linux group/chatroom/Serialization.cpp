#include <iostream>
#include <json.hpp>
#include "Serialization.hpp"
#include "user.hpp"
using std::string, std::cout, std::endl, nlohmann::json;

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
// 把这俩个合到一起
string From_Frd(int opt, int ID, int oppositeID)
{
    json j = {
        {"option", opt},
        {"ID", ID},
        {"oppositeID", oppositeID}};
    return j.dump();
}

/*














*/

string To_Json_User(UserTotal usr)
{
    // json frd_arr = json::array();
    json frd_map(usr.frd);
    json grp_map(usr.grp);
    // for (const auto &f : usr.frd)
    // {
    //     json f_json;
    //     f_json["ID"] = f.ID;
    //     frd_arr.push_back(f_json);
    // } // 放到另一个函数

    // json frd_arr = j["frd"];
    // for (const auto &f : frd_arr)
    // {
    //     UserBase f_user;
    //     f_user.ID = f["ID"];
    //     f_user.account = f["account"];
    //     f_user.password = f["password"];
    //     f_user.islogin = f["islogin"];
    //     user.frd.push_back(f_user);
    // }
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

void Get_Info(const string &jso, int *ID, string *account, string *password, int *oppositeID)
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
    // *account = j["account"];
    // *password = j["password"];
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

// string To_Json_Friend(UserTotal usr)
// {

//     json j = {
//         {"ID", usr.ID},
//         {"account", usr.account},
//         {"islogin", usr.islogin}
//         };
//     return j.dump();
// }