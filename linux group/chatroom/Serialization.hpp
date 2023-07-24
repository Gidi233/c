#ifndef JSON
#define JSON
#include <string>
#include <json.hpp>
#include "user.hpp"
using std::string, nlohmann::json;

string From_Main(int opt, string account, string password);
UserTotal From_Json_User(string j);

string To_Json_User(UserTotal usr);
int getopt(const string &jso);
void Get_Ac_Pa(const string &jso, string *account, string *password);
// UserTotal New_User(string jso);

#endif