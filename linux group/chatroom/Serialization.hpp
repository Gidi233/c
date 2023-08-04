#ifndef JSON
#define JSON
#include <iostream>
#include <json.hpp>
#include <unordered_map>
#include <list>
#include "user.hpp"
#include "event.hpp"
#include "Message.hpp"
#include "group.hpp"

using std::string, nlohmann::json;

string Get_Type(string jso);
int Get_Num(string jso);
void From_Json_Chat(string jso);
string From_Main(int opt, string account, string password);
string From_Self(int opt, int ID);
string From_Manage(int opt, int ID, int oppositeID, int num);
void From_Json_Frdlist(string jso);
string From_Frd(int opt, int ID, int frdID);
string From_Frd_Account(int opt, string opposite_account);
UserTotal From_Json_UserTotal(string j);
UserBase From_Json_UserBase(string jso);

void From_Json_Grplist(string jso);

string Set_Type(string jso, bool flag);
string Set_Num(int num);
string To_Json_User(UserTotal usr);
json To_Json_MsgList(list<Message> qu);
list<Message> From_Json_MsgList(json j);
string Get_Notice(string jso);
json To_Notice(string jso);
string Notice_Clear(string jso);
string Get_Manage(string jso);
json To_Manage(string jso);
Event getopt(const string &jso);
string To_UserBase(string jso);
string Change_isLogin(string jso);
void Get_Info(const string &jso, int *ID, string *account, string *password, int *oppositeID, string *opposite_account);
string Add_Friend(int ID, string json, int chatID);
Message From_Json_Msg(string jso);
string To_Json_Msg(Message msg);
string Add_Msg(string msg, string chat);
string Add_Notice(string jso, Message msg);
string Add_Manage(string jso, Message msg);
string Del_Manage(string jso);
string To_Json_Frdlist(const UserTotal usr);

string To_Json_Grplist(const unordered_map<int, int> grp_map);
string To_GrpBase(string jso);
string To_Json_Grp(Group grp);
#endif