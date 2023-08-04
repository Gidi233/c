#include "group.hpp"
using std::cout, std::endl;

Group::Group() {}
Group::Group(int gid, string name1) : GID(gid), name(name1) {}

void Group::toString()
{
    cout << "GID:" << GID << "\n群名：" << name << endl;
}