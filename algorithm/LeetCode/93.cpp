
class Solution
{
public:
    vector<string> ans;
    void dfs(string s, int num)
    {
        int pos = s.find_last_of('.') + 1;
        if (pos == s.size())
            return;
        int i = stoi(s.substr(pos, 4));
        if (num == 3)
        {
            if ((s.size() - pos == 3 && 99 < i && i < 256) ||
                (s.size() - pos == 2 && 9 < i && i < 100) || (s.size() - pos == 1 && i < 10))
                ans.push_back(s);
            return;
        }
        string tmp = s;
        dfs(s.insert(pos + 1, "."), num + 1);
        s = tmp;
        i = stoi(s.substr(pos, 2)); // 直接s[pos]!='0'就行
        if (9 < i)
        {
            dfs(s.insert(pos + 2, "."), num + 1);
            s = tmp;
        }
        i = stoi(s.substr(pos, 3));
        if (99 < i && i < 256)
        {
            dfs(s.insert(pos + 3, "."), num + 1);
            s = tmp;
        }
    }
    vector<string> restoreIpAddresses(string s)
    {
        dfs(s, 0);
        return ans;
    }
};
// 回溯
// 感觉递归不如四层循环，当a+b+c+d==s.size()时（即先找到四段长度分配正确的地址），再进行逻辑判断其中数字大小是否合法。
// 递归在错误的长度分配时，也会进行逻辑判断