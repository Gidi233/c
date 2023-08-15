#ifndef DATABASE
#define DATABASE

#include <hiredis/hiredis.h>
#include <string>
using std::string;

// 都是static的话 是不是不用建这个类

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

    static bool File_Exist(string name);
    static bool File_In(string name, size_t offset);
    static size_t File_Out(string name);

    static int Get_ChatID();
    static bool Del_Chat(int ID);
    static bool Chat_In(int ID, string jso);
    static string Chat_Out(int ID);

    static int Get_GID();
    static bool Set_Name_To_GID(int ID, string name);
    static bool Grp_Exist_name(string name);
    static bool Grp_Exist_ID(int ID);
    static bool Del_GrpName(string name);
    static bool Del_Grp(int ID);
    static bool Grp_In(int ID, string jso);
    static string Grp_Out(int ID);

    static void Close();
};
#endif