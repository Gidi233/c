#ifndef SERVICE_SER
#define SERVICE_SER
#include <string>
using std::string;
void Getfd(int fd);
void Send(int fd, string jso);
void SendBool(int fd, bool flag);
string Recv(int fd);

#endif