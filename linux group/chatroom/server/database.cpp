#include "database.hpp"
#include <iostream>
redisContext *Database::redis = nullptr; // 不能在这里直接redisConnect("127.0.0.1", 6379)

bool Database::Init()
{
    redis = redisConnect("127.0.0.1", 6379); // Database::
    if (redis == nullptr || redis->err)
    {
        std::cerr << "Failed to connect Redis: " << redis->errstr << std::endl;
        return 0;
    }
    return 1;
}

int Database::GetID()
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "EXISTS UserID");
    bool flag = reply->integer;
    freeReplyObject(reply);
    if (flag)
    {
        reply = (redisReply *)redisCommand(Database::redis, "GET UserID");
        int ans = std::stoi(reply->str);
        freeReplyObject(reply);
        reply = (redisReply *)redisCommand(Database::redis, "SET UserID %d", ans + 1);
        freeReplyObject(reply);
        return ans;
    }
    else
    {
        reply = (redisReply *)redisCommand(Database::redis, "SET UserID %d", 2);
        freeReplyObject(reply);
        return 1;
    }
}

bool Database::Set_Account_ID(int ID, string account)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "SET Username:%s %d", account.c_str(), ID);
    string ans(reply->str);
    freeReplyObject(reply);
    return ans == "OK";
}
int Database::Get_Account_ID(string account)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "GET Username:%s", account.c_str());
    int ans = std::stoi(reply->str);
    freeReplyObject(reply);
    return ans;
}

bool Database::User_In(int ID, string jso)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "SET User:%d %s", ID, jso.c_str());
    string ans(reply->str);
    freeReplyObject(reply);
    return ans == "OK";
}

bool Database::User_Exist(string account)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "EXISTS Username:%s", account.c_str());
    if (reply == nullptr)
    {
        return false;
    }
    bool ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

string Database::User_Out(int ID)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "GET User:%d", ID);
    string ans(reply->str);
    freeReplyObject(reply);
    return ans;
}

// bool Change_isLogin()
// {
// }

void Database::Close()
{
    redisFree(redis);
    return;
}
