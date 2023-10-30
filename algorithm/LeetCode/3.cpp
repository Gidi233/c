class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_set<char> set;
        int l = 0, r = 0;
        int ans = 0;
        while (r < s.size())
        {
            if (set.count(s[r]))
            {
                ans = max(ans, r - l);
                set.erase(s[l]);
                l++;//见下
            }
            else
            {
                set.emplace(s[r]);
                r++;
            }
        }
        return max(ans, r - l);
    }
};
//滑动窗口

// 每次左指针右移一位，移除set的一个字符，这一步会导致很多无用的循环。while循环发现的重复字符不一定就是Set最早添加那个，还要好多次循环才能到达，这些都是无效循环，不如直接用map记下每个字符的索引，直接进行跳转
// map解法如下
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_map<char, int> map;
        int l = 0, r = 0;
        int ans = 0;
        while (r < s.size())
        {
            if (map.count(s[r]) && map[s[r]] >= l)
            {
                ans = max(ans, r - l);
                l = map[s[r]];
            }
            map[s[r]] = r + 1;
            r++;
        }
        return max(ans, r - l);
    }
};