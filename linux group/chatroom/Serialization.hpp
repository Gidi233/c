#ifndef JSON
#define JSON
#include <string>
#include <json.hpp>
#include "user.hpp"
using std::string, nlohmann::json;

string From_Main(int opt, string account, string password);
// bool To_Main(string jso);
UserTotal From_Json_User(string j);

string To_Json_User(UserTotal usr);
int getopt(const string &jso);
UserTotal New_User(string jso);

#endif