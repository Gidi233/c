#ifndef DATABASE
#define DATABASE

#include <hiredis/hiredis.h>
#include <string>
using std::string;

class Database
{
public:
    static redisContext *redis;
    static bool Init();
    static int GetID();
    static bool User_In(string account, string jso);
    static bool User_Exist(string account);
    static string User_Out(string account);
    // static bool Change_isLogin();
    static void Close();
};
#endif