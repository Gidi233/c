#include "database.hpp"

redisContext *Database::redis = redisConnect("127.0.0.1", 6379);

bool Database::User_In(string account, string jso)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "SET User%s %s", account.c_str(), jso.c_str());
    string ans(reply->str);
    freeReplyObject(reply);
    return ans == "OK";
}

bool Database::User_Exist(string account)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "EXISTS User%s", account.c_str());
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
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "GET User%s", account.c_str());
    string ans(reply->str);
    freeReplyObject(reply);
    return ans;
}

void Database::Close()
{
    redisFree(Database::redis);
    return;
}
