#ifndef MESSAGE
#define MESSAGE
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

using std::string, std::cout;
class Message
{
public:
    int SendID, ReceiveID;
    string Send_Account, Receive_Account, Str, Time;

    int Event;
    // 0:消息 1：加好友 2：删好友

    // Message(int sendID, string send_account, int receiveID, string str, string time);
    // Message(int event, int sendID, string send_account, int receiveID, string receive_account, string time);
    void toString();
};

string gettime();
#endif
