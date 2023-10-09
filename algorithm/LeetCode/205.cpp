#include <bits/stdc++.h>
using namespace std;

bool isIsomorphic(string s, string t)
{
    unordered_map<char, char> k, v;
    for (int i = 0; i < s.size(); i++)
    {
        if (k.count(s[i]))
        {
            if (t[i] != k[s[i]])
                return 0;
        }
        else
        {
            if (v.count(t[i]))
                return 0;
            k[s[i]] = t[i];
            v[t[i]] = s[i];
        }
    }
    return 1;
}
// 不知道力扣的测试程序哪里坏了，官方答案都过不去
// 哈希 s对应t同时不能有其他s对应同一个t，拿两个表分别存一下k2v（s对应的t是否相同）、v2k（t是否已经有对应）