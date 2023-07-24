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

/*














*/

string To_Json_User(UserTotal usr)
{
    // json frd_arr = json::array();
    // for (const auto &f : usr.frd)
    // {
    //     json f_json;
    //     f_json["ID"] = f.ID;
    //     f_json["account"] = f.account;
    //     f_json["password"] = f.password;
    //     f_json["islogin"] = f.islogin;
    //     frd_arr.push_back(f_json);
    // }//放到另一个函数

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
        // {"frd",frd_arr}
    };
    return j.dump();
}

UserTotal From_Json_User(string jso)
{
    json j = json::parse(jso);
    return UserBase(j.at("ID"), j["account"], j["password"], j["islogin"]);
}

/*









*/
int getopt(const string &jso)
{
    json j = json::parse(jso);
    return j.at("option");
}

void Get_Ac_Pa(const string &jso, string *account, string *password)
{
    json j = json::parse(jso);
    *account = j.at("account");
    *password = j.at("password");
    // *account = j["account"];
    // *password = j["password"];
}