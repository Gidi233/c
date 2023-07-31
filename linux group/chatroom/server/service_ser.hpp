#ifndef SERVICE_SER
#define SERVICE_SER
#include <string>
#include "../user.hpp"
using std::string;
void Getfd(int fd);
void Send(int fd, string jso, bool type);
void SendInt(int fd, int num);
string Recv(int fd);
UserTotal New_User(string account, string password);
bool Change_isLogin_Ser(int ID);

#endif