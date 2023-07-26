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

bool Database::User_In(string account, string jso)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "SET User:%s %s", account.c_str(), jso.c_str());
    string ans(reply->str);
    freeReplyObject(reply);
    return ans == "OK";
}

bool Database::User_Exist(string account)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "EXISTS User:%s", account.c_str());
    if (reply == nullptr)
    {
        return false;
    }
    bool ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}
string Database::User_Out(string account)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "GET User:%s", account.c_str());
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
