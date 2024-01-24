#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int myAtoi(string s)
    {
        long i = 0, ans = 0;
        bool flag = false;
        while (s[i] == ' ')
        {
            i++;
            if (i == s.length())
                return 0;
        }
        if (s[i] == '-')
        {
            flag = 1;
            i++;
        }
        else if (s[i] == '+')
            i++;
        while (s[i] == '0')
        {
            i++;
            if (i == s.length())
                return 0;
        }

        while (s[i] >= '0' && s[i] <= '9')
        {
            long tmp = ans * 10 + s[i] - '0'; // 用int可能会溢出  可以把ans和 INT_MAX 除以 10 进行比较。
            if (!flag)
            {
                if (tmp <= INT_MAX)
                    ans = tmp;
                else
                    return INT_MAX;
            }
            else
            {

                if (-tmp >= INT_MIN)
                    ans = tmp;
                else
                    return INT_MIN;
            }
            i++;
            if (i == s.length())
                break;
        }
        return flag ? -ans : ans;
    }
};


class Automaton
{
    string state = "start";
    unordered_map<string, vector<string>> table = {//把这群东西换成enum
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}};

    int get_col(char c)
    {
        if (isspace(c))
            return 0;
        if (c == '+' or c == '-')
            return 1;
        if (isdigit(c))
            return 2;
        return 3;
    }

public:
    int sign = 1;
    long long ans = 0;

    void get(char c)
    {
        state = table[state][get_col(c)];
        if (state == "in_number")
        {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
        }
        else if (state == "signed")
            sign = c == '+' ? 1 : -1;
    }
};

class Solution
{
public:
    int myAtoi(string str)
    {
        Automaton automaton;
        for (char c : str)
            automaton.get(c);
        return automaton.sign * automaton.ans;
    }
};
// 确定有限状态机