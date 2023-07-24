#ifndef SERVICE_SER
#define SERVICE_SER
#include <string>
#include "../user.hpp"
using std::string;
void Getfd(int fd);
void Send(int fd, string jso);
void SendBool(int fd, bool flag);
string Recv(int fd);
UserTotal New_User(string account, string password);

#endif