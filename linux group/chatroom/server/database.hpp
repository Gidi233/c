#ifndef DATABASE
#define DATABASE

#include <hiredis/hiredis.h>
#include <string>
using std::string;

// 都是static的话是不是不用建这个类

class Database
{
public:
    static redisContext *redis;

    static bool Init();
    static int GetID();
    static bool Set_Account_To_ID(int ID, string account);
    static int Get_Account_To_ID(string account);

    static bool User_In(int ID, string jso);
    static string User_Out(int ID);
    static bool User_Exist_Account(string account);
    static bool User_Exist_ID(int ID);

    static int Get_ChatID();
    static bool Chat_In(int ID, string jso);
    static string Chat_Out(int ID);
    // static bool Change_isLogin();
    static void Close();
};
#endif