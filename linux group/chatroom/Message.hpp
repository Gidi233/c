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
    string Send_Account, Receive_Account = "", Str = "", Time;

    Event event;
    // 初始化列表中的顺序应与类定义中的成员顺序相匹配???是不是有这条规则来着
    Message();
    Message(Event event, int sendID, string send_account, int receiveID, string time);
    Message(Event event, int sendID, string send_account, int receiveID, string time, int num);
    Message(Event event, int sendID, string send_account, int receiveID, string str, string time);
    Message(Event event1, int sendID1, string send_account1, int receiveID1, string recv_account1, string str1, string time1, int num1);

    void toString();
};

struct MessageComparator
{
    bool operator()(const Message &message1, const Message &message2) const
    {
        if (message1.SendID == message2.SendID && message1.ReceiveID == message2.ReceiveID && message1.event == message2.event)
            return false;
        else
            return message1.Time < message2.Time;
    }
};

// struct MessageHash {
//     std::size_t operator()(const Message &m) const
//     {
//         std::size_t h1 = std::hash<int>()(m.SendID);
//         std::size_t h2 = std::hash<Event>()(m.event);  // If std::hash is defined for Event
//         std::size_t h3 = std::hash<int>()(m.ReceiveID);
//         std::size_t h4 = std::hash<std::string>()(m.Str);
//         return h1 ^ h2 ^ h3 ^ h4;
//     }
// };

// struct MessageEqual {
//     bool operator()(const Message &lhs, const Message &rhs) const
//     {
//         return lhs.event == rhs.event &&
//                lhs.SendID == rhs.SendID &&
//                lhs.ReceiveID == rhs.ReceiveID &&
//                lhs.Str == rhs.Str;
//     }
// };

string gettime();
#endif
