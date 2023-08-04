#include "Message.hpp"
#include "client/client.hpp"

Message::Message()
{
}

Message::Message(Event event1, int sendID1, string send_account1, int receiveID1, string time1) : event(event1), SendID(sendID1), Send_Account(send_account1), ReceiveID(receiveID1), Time(time1)
{
}

Message::Message(Event event1, int sendID1, string send_account1, int receiveID1, string time1, int num1) : event(event1), SendID(sendID1), Send_Account(send_account1), ReceiveID(receiveID1), Time(time1), num(num1)
{
}

Message::Message(Event event1, int sendID1, string send_account1, int receiveID1, string str1, string time1) : event(event1), SendID(sendID1), Send_Account(send_account1), ReceiveID(receiveID1), Str(str1), Time(time1)
{
}

Message::Message(Event event1, int sendID1, string send_account1, int receiveID1, string recv_account1, string str1, string time1, int num1) : event(event1), SendID(sendID1), Send_Account(send_account1), ReceiveID(receiveID1), Receive_Account(recv_account1), Str(str1), Time(time1), num(num1)
{
}

void Message::toString()
{
    // cout << "用户" << Send_Account << "(ID:" << SendID << ")向你发送了";
    switch (event)
    {
    case Sendmsg_Tofrd:
        // 分为群聊和私聊
        if (client::frdID == SendID || client::frdID == ReceiveID)
        {
            cout << "用户:" << Send_Account << "(ID:" << SendID << "):" << Time << endl;
            cout << Str << endl;
        }
        else
        {
            cout << "用户:" << Send_Account << "(ID:" << SendID << ")向你发送了一条消息\n";
        }
        break;

    case Send_Add_Frd:
        cout << "用户:" << Send_Account << "(ID:" << SendID << ")向你发送了一条好友申请\n";
        break;
    case Recv_Add_Frd:
        if (num)
            cout << "用户:" << Send_Account << "(ID:" << SendID << ")接受了你的好友申请\n";
        else
            cout << "用户:" << Send_Account << "(ID:" << SendID << ")拒绝了你的好友申请\n";
        break;
    case Del_Frd:

        cout << "用户:" << Send_Account << "(ID:" << SendID << ")刪除了你\n";
        break;
    default:
        break;
    }
}

string gettime()
{
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 将当前时间点转换为 time_t 类型
    std::time_t t = std::chrono::system_clock::to_time_t(now); // 不一定要

    // 使用 std::put_time 函数将时间格式化为字符串
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}