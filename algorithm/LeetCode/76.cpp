#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    unordered_map<char, int> num;
    bool find(char c)
    {
        for (auto i : num)
        {
            if (c == i.first)
                return 1;
        }
        return 0;
    }
    bool all()
    {
        for (auto i : num)
        {
            if (i.second > 0)
                return 0;
        }
        return 1;
    }

public:
    string minWindow(string s, string t)
    {
        queue<int> index;//记录左指针的下一个下标
        int ans_index = 0, ans_length = INT_MAX, length = s.length();
        for (char c : t)
        {
            ++num[c];
        }
        int l = 0, r = 0;
        bool flag = 1;
        while (!find(s[l]) && l < length)
        {
            ++l;
        }
        r = l;

        num[s[r]]--;
        r++;
        while (1)
        {
            while (!(flag = all()) && r < length)
            {
                if (find(s[r]))
                {
                    index.push(r);
                    num[s[r]]--;
                }
                r++;
            }
            
            do
            {
                if (flag)
                {
                    if (r - l < ans_length)
                    {
                        ans_index = l;
                        ans_length = r - l;
                        if (ans_length == t.length())
                            return ans_length == INT_MAX ? "" : s.substr(ans_index, ans_length);
                    }
                }
                else
                    return ans_length == INT_MAX ? "" : s.substr(ans_index, ans_length);

                num[s[l]]++;
                l = index.front();
                index.pop();
            } while (flag=all());
        }
    }
};
// 滑动窗口用队列存左指针的下一个下标， unordered_map记录t中字符出现次数，>0时 窗口中 对应字符出现次数不够
