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
    static bool Set_Account_ID(int ID, string account);
    static int Get_Account_ID(string account);
    static bool User_In(int ID, string jso);
    static bool User_Exist(string account);
    static string User_Out(int account);
    // static bool Change_isLogin();
    static void Close();
};
#endif