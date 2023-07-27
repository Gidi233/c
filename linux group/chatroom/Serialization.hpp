#ifndef JSON
#define JSON
#include <string>
#include <json.hpp>
#include "user.hpp"
using std::string, nlohmann::json;

string From_Main(int opt, string account, string password);
string From_Self(int opt, int ID); //
string From_Frd(int opt, int ID, int frdID);
UserTotal From_Json_UserTotal(string j);
UserBase From_Json_UserBase(string jso);

string To_Json_User(UserTotal usr);
int getopt(const string &jso);
void Get_Info(const string &jso, int *ID, string *account, string *password, int *oppositeID);
string Add_Friend(int ID, string json, int chatID);
string Change_isLogin(string jso);
// UserTotal New_User(string jso);

#endif