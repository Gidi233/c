#ifndef GROUP
#define GROUP
#include <iostream>
#include <unordered_map>
#include "server/database.hpp"

using std::unordered_map, std::string;

class Group
{
public:
    int GID, ChatID;
    string name;
    unordered_map<int, int> mem; // 0:群员 1:管理员 2:群主

    Group();
    Group(int chatID, string name1);
    Group(int gid, int chatID, string name1);
    Group(int gid, int chatID, string name1, unordered_map<int, int> mem);

    void toString();
};

#endif