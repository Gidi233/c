#include "./server/database.hpp"
#include "user.hpp"

UserBase::UserBase() {}

UserBase::UserBase(string account1, string password1) : account(account1), password(password1) {}
UserBase::UserBase(int ID1, string account1, bool islogin1) : ID(ID1), account(account1), islogin(islogin1) {}

UserBase::UserBase(int ID1, string account1, string password1, bool islogin1) : ID(ID1), account(account1), password(password1), islogin(islogin1) {}

UserBase::~UserBase() {}

void UserBase::toString()
{
    cout << "ID:" << ID << "\n用户名:" << account << endl;
    if (islogin)
        cout << "在线\n";
    else
        cout << "离线\n";
}

UserTotal::UserTotal() {}

UserTotal::UserTotal(const UserBase &base) : UserBase(base) // 注册用
{
    if (!ID)
    {
        islogin = 1;
        ID = Database::GetID();
    }
}

UserTotal::UserTotal(const UserBase &base, unordered_map<int, int> friends, unordered_map<int, bool> Block, unordered_map<int, int> group, list<Message> notice1, list<Message> manage1) : UserBase(base), frd(friends), frd_Block(Block), grp(group), notice(notice1), manage(manage1) // 数据库取数据用
{
}

UserTotal::~UserTotal()
{
}
