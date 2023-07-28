#include "Message.hpp"

void Message::toString()
{
    cout << "用户" << Send_Account << "(ID:" << SendID << ")向你发送了";
    switch (Event)
    {
    case 0:
        /* code */
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