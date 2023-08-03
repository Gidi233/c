#ifndef MESSAGE
#define MESSAGE
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "event.hpp"

using std::string, std::cout;
class Message
{
public:
    int SendID, ReceiveID, num = 0;
    string Send_Account, Receive_Account = "", Str, Time;

    Event event;
    // 初始化列表中的顺序应与类定义中的成员顺序相匹配???是不是有这条规则来着
    Message();
    Message(Event event, int sendID, string send_account, int receiveID, string time);
    Message(Event event, int sendID, string send_account, int receiveID, string time, int num);
    Message(Event event, int sendID, string send_account, int receiveID, string str, string time);
    Message(Event event1, int sendID1, string send_account1, int receiveID1, string recv_account1, string str1, string time1, int num1);
    void toString();
};

string gettime();
#endif
