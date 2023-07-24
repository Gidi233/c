#ifndef DATABASE
#define DATABASE

#include <hiredis/hiredis.h>
#include <string>
using std::string;

class Database
{
public:
    static redisContext *redis;
    // void Init();
    static bool User_In(string account, string jso);
    static bool User_Exist(string account);
    static string User_Out(string account);
    static void Close();
};
#endif