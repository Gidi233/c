#ifndef JSON
#define JSON
#include <iostream>
#include <nlohmann/json.hpp> //for arch
#include <unordered_map>
#include <list>
#include "user.hpp"
#include "File.hpp"
#include "server/server.hpp"
#include "event.hpp"
#include "Message.hpp"
#include "group.hpp"

using std::string, nlohmann::json;

string Get_Type(string jso);
long long Get_Num(string jso);
void From_Json_Chat(string jso);
string From_Main(int opt, string account, string password);
string From_Self(int opt, int ID);
string From_File(int opt, int ID, int num, long offset);
string From_Manage(int opt, int ID, int otherUsrID, int num);

void From_Json_Frdlist(string jso);
string From_Frd(int opt, int ID, int frdID);
string From_Frd_File(int opt, int ID, int frdID, string filename, size_t size, string filehash);
string From_Frd_Account(int opt, string otherUsr_account);
UserTotal From_Json_UserTotal(string j);
UserBase From_Json_UserBase(string jso);

string From_Grp(int opt, int ID, int gid);
string From_Grp_Name(int opt, int ID, string name);
string From_Grp_Only(int opt, int gid);
string From_Grp_Usr(int opt, int ID, int gid, int uid);
void From_Json_Grplist(string jso);
void From_Json_Grp_Member_List(string jso);

string Set_Type(string jso, bool flag);
string Set_Num(long long num);
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

File From_Json_File(string jso);
string To_Json_File(File f);
list<File> From_Json_FileList(json j);
json To_Json_FileList(list<File> qu);
string Get_File(string jso);
long Get_Offset(string jso);
json To_File(string jso);

void Get_Fileinfo(const string &jso, string *filename, size_t *size, string *filehash);
void Get_Info(const string &jso, int *ID, string *account, string *password, int *otherUsrID, string *otherUsr_account, int *grpID, string *grp_account);
string Add_Friend(int ID, string json, int chatID);
Message From_Json_Msg(string jso);
string To_Json_Msg(Message msg);
string Add_Msg(string msg, string chat);
string Add_Notice(string jso, Message msg);
string Add_Manage(string jso, Message msg);
string To_Json_Frdlist(const UserTotal usr);

string To_Json_Grplist(const unordered_map<int, int> grp_map);
string To_GrpBase(string jso);
string To_Json_Grp(Group grp);
Group From_Json_Grp(string jso);
string To_Json_Grp_Member_List(const unordered_map<int, int> mem_map);
json To_Json_Manage_List(set<Message, MessageComparator> qu);
set<Message, MessageComparator> From_Json_Manage_List(json j);

#endif