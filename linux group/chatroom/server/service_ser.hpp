#ifndef SERVICE_SER
#define SERVICE_SER
#include <string>
#include "../user.hpp"
#include "../group.hpp"
using std::string;
void Getfd(int *fd);
void Send(int fd, string jso, bool type);
void SendInt(int fd, long long num);
string Recv(int fd);
void Relay_To_User(int otherUsrID, Message msg);
UserTotal New_User(string account, string password);
bool Change_isLogin_Ser(int ID);

#endif