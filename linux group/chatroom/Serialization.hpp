#ifndef JSON
#define JSON
#include <string>
#include <json.hpp>
#include <list>
#include "user.hpp"
#include "event.hpp"

using std::string, nlohmann::json;

string Get_Type(string jso);
int Get_Num(string jso);
string From_Main(int opt, string account, string password);
string From_Self(int opt, int ID); //
list<UserBase> From_Json_Frdlist(string jso);
string From_Frd(int opt, int ID, int frdID);
string From_Frd_Account(int opt, string opposite_account);
UserTotal From_Json_UserTotal(string j);
UserBase From_Json_UserBase(string jso);

string Set_Type(string jso, bool flag);
string Set_Num(int num);
string To_Json_User(UserTotal usr);
Event getopt(const string &jso);
string To_UserBase(string jso);
void Get_Info(const string &jso, int *ID, string *account, string *password, int *oppositeID, string *opposite_account);
string Add_Friend(int ID, string json, int chatID);
string Change_isLogin(string jso);
string To_Json_Frdlist(const unordered_map<int, int> &frd);
// UserTotal New_User(string jso);

#endif