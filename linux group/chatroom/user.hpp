#ifndef USER
#define USER
#include <list>
#include <unordered_map>
#include <iostream>
#include "Message.hpp"
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
    UserBase(int ID1, string account1, bool islogin1);
    UserBase(int ID1, string account1, string password1, bool islogin1);
    void toString();
    ~UserBase();
};

class UserTotal : public UserBase
{
public:
    unordered_map<int, int> frd; // 对象ID对聊天数据ID
    unordered_map<int, bool> frd_Block;
    unordered_map<int, int> grp;
    list<Message> notice, manage;

    // UserTotal(int ID, string account, string password, bool islogin);//说在UserTotal类中找不到这些成员
    UserTotal();
    UserTotal(const UserBase &base);
    UserTotal(const UserBase &base, unordered_map<int, int> frd, unordered_map<int, bool> frd_Block, unordered_map<int, int> grp, list<Message> notice, list<Message> manage);
    ~UserTotal();
};

#endif