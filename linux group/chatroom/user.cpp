#include "user.hpp"

int UserTotal::totalID = 0;

UserBase::UserBase() {}

UserBase::UserBase(int ID1, string account1, string password1, bool islogin1) : ID(ID1), account(account1), password(password1), islogin(islogin1)
{
}

UserBase::UserBase(string account1, string password1) : account(account1), password(password1) {}

UserBase::~UserBase() {}

UserTotal::UserTotal() {}

UserTotal::UserTotal(const UserBase &base) : UserBase(base)
{
    if (!ID)
    {
        islogin = 1;
        ID = ++totalID;
    }
}

UserTotal::~UserTotal()
{
}

void UserTotal::toString()
{
    cout << "ID:" << ID << "\n用户名:" << account << endl;
    if (islogin)
        cout << "在线\n";
    else
        cout << "离线\n";
}