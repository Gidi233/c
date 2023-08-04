#include "group.hpp"
using std::cout, std::endl;

Group::Group() {}
Group::Group(int chatID, string name1) : ChatID(chatID), name(name1) // 新建用
{
    GID = Database::Get_GID();
}
Group::Group(int gid, int chatID, string name1) : GID(gid), ChatID(chatID), name(name1) {}
Group::Group(int gid, int chatID, string name1, unordered_map<int, int> mem1) : GID(gid), ChatID(chatID), name(name1), mem(mem1) {}

void Group::toString()
{
    cout << "GID:" << GID << "\n群名：" << name << endl;
}