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
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HEXISTS User UserID");
    bool flag = reply->integer;
    freeReplyObject(reply);
    if (flag)
    {
        reply = (redisReply *)redisCommand(Database::redis, "HGET User UserID");
        int ans = std::stoi(reply->str);
        freeReplyObject(reply);
        reply = (redisReply *)redisCommand(Database::redis, "HSET User UserID %d", ans + 1);
        freeReplyObject(reply);
        return ans;
    }
    else
    {
        reply = (redisReply *)redisCommand(Database::redis, "HSET User UserID %d", 2);
        freeReplyObject(reply);
        return 1;
    }
}

bool Database::Set_Account_To_ID(int ID, string account)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HSET Username %s %d", account.c_str(), ID);
    int ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}
int Database::Get_Account_To_ID(string account)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HGET Username %s", account.c_str());
    int ans = std::stoi(reply->str);
    freeReplyObject(reply);
    return ans;
}

bool Database::User_In(int ID, string jso)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HSET User %d %s", ID, jso.c_str());
    int ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

string Database::User_Out(int ID)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HGET User %d", ID);
    string ans(reply->str);
    freeReplyObject(reply);
    return ans;
}

bool Database::User_Exist_Account(string account)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HEXISTS Username %s", account.c_str());
    if (reply == nullptr)
    {
        return false;
    }
    bool ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

bool Database::User_Exist_ID(int ID)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HEXISTS User %d", ID);
    if (reply == nullptr)
    {
        return false;
    }
    bool ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

int Database::Get_ChatID()
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HEXISTS Chat ChatID");
    bool flag = reply->integer;
    freeReplyObject(reply);
    if (flag)
    {
        reply = (redisReply *)redisCommand(Database::redis, "HGET Chat ChatID");
        int ans = std::stoi(reply->str);
        Chat_In(ans, "{\"chat\":null}"); //
        // 在这建一个库reply = (redisReply *)redisCommand(Database::redis, "HSET Chat:%d  ", ans + 1);
        freeReplyObject(reply);
        reply = (redisReply *)redisCommand(Database::redis, "HSET Chat ChatID %d", ans + 1);
        freeReplyObject(reply);
        return ans;
    }
    else
    {
        reply = (redisReply *)redisCommand(Database::redis, "HSET Chat ChatID %d", 2);
        freeReplyObject(reply);
        Chat_In(1, "{\"chat\":null}");
        return 1;
    }
}

bool Database::Chat_In(int ID, string jso)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HSET Chat %d %s", ID, jso.c_str());
    int ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

string Database::Chat_Out(int ID)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HGET Chat %d", ID);
    string ans(reply->str);
    freeReplyObject(reply);
    return ans;
}

bool Database::Del_Chat(int ID)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HDEL Chat %d", ID);
    int ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

int Database::Get_GID()
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HEXISTS Grp GrpID");
    bool flag = reply->integer;
    freeReplyObject(reply);
    if (flag)
    {
        reply = (redisReply *)redisCommand(Database::redis, "HGET Grp GrpID");
        int ans = std::stoi(reply->str);
        freeReplyObject(reply);
        reply = (redisReply *)redisCommand(Database::redis, "HSET Grp GrpID %d", ans + 1);
        freeReplyObject(reply);
        return ans;
    }
    else
    {
        reply = (redisReply *)redisCommand(Database::redis, "HSET Grp GrpID %d", 2);
        freeReplyObject(reply);
        return 1;
    }
}

bool Database::Set_Name_To_GID(int ID, string name)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HSET Grpname %s %d", name.c_str(), ID);
    int ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

bool Database::Grp_Exist_name(string name)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HEXISTS Grpname %s", name.c_str());
    if (reply == nullptr)
    {
        return false;
    }
    bool ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

bool Database::Grp_Exist_ID(int ID)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HEXISTS Grp %d", ID);
    if (reply == nullptr)
    {
        return false;
    }
    bool ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

bool Database::Del_GrpName(string name)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HDEL Grpname %s", name.c_str());
    int ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

bool Database::Del_Grp(int ID)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HDEL Grp %d", ID);
    int ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

bool Database::Grp_In(int ID, string jso)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HSET Grp %d %s", ID, jso.c_str());
    int ans = reply->integer;
    freeReplyObject(reply);
    return ans;
}

string Database::Grp_Out(int ID)
{
    redisReply *reply = (redisReply *)redisCommand(Database::redis, "HGET Grp %d", ID);
    string ans(reply->str);
    freeReplyObject(reply);
    return ans;
}

void Database::Close()
{
    redisFree(redis);
    return;
}
