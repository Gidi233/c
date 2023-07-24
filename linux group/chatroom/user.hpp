#ifndef USER
#define USER
#include <queue>
#include <list>
#include <iostream>
using namespace std;

class UserBase
{
public:
    int ID = 0;
    string account;
    string password;
    bool islogin; // protect?

    UserBase();
    UserBase(string account1, string password1);
    UserBase(int ID1, string account1, string password1, bool islogin1);
    ~UserBase();
};

class UserTotal : public UserBase
{
public:
    list<UserBase> frd;
    // list<group> grp;
    // list<queue<massege>> msg_frd,msg_grp;map??聊天记录
    static int totalID; // 要在类外初始化//int UserTotal::totalID = 0;

    // UserTotal(int ID, string account, string password, bool islogin);//说在UserTotal类中找不到这些成员
    UserTotal();
    UserTotal(const UserBase &base);
    ~UserTotal();
    void toString();
};

#endif