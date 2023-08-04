#ifndef GROUP
#define GROUP
#include <iostream>
#include <unordered_map>

using std::unordered_map, std::string;

class Group
{
public:
    int GID, ChatID;
    string name;
    unordered_map<int, int> mem; // 0:群员 1:管理员 2:群主

    Group();
    Group(int gid, string name1);

    void toString();
};

#endif