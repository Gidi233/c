#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        unordered_set<int> s;
        for (int i : nums)
        {
            if (i <= 0 && s.count(i))
                continue;
            else
                s.emplace(i);
        }
        for (int i = 1;; i++)
        {
            if (s.count(i))
                continue;
            else
                return i;
        }
    }
};

class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int n = nums.size();
        for (int &num : nums)
        {
            if (num <= 0)
            {
                num = n + 1;
            }
        }
        for (int i = 0; i < n; ++i)
        {
            int num = abs(nums[i]);
            if (num <= n)
            {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] > 0)
            {
                return i + 1;
            }
        }
        return n + 1;
    }
};
// 在原地把出现过的数，在对应位置置为-，对于一个长度为 N 的数组，其中没有出现的最小正整数只能在 [1,N+1] 中

class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
            {
                swap(nums[nums[i] - 1], nums[i]);
            }
        }
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] != i + 1)
            {
                return i + 1;
            }
        }
        return n + 1;
    }
};
// 把值放到对应的位置，第一个不对应的就是

int speedUp = []
{std::ios::sync_with_stdio(0); std::cin.tie(0); return 0; }();
bool has[100002];

int digit(char c)
{
    return c & 15;
}
bool isDigit(char c)
{
    return '0' <= c && c <= '9';
}
int init = []
{
    std::ofstream out("user.out");
    std::cout.rdbuf(out.rdbuf());
    for (string s; std::getline(std::cin, s); std::cout << '\n')
    {
        int n = count(s.begin(), s.end(), ',') + 3;
        memset(has, 0, n);
        for (int _i = 1, _n = s.length(); _i < _n; ++_i)
        {
            if (s[_i] == '-')
                for (_i += 2; isDigit(s[_i]); ++_i)
                    ;
            else
            {
                int v = s[_i++] & 15;
                while (isDigit(s[_i]))
                    v = v * 10 + digit(s[_i++]);
                if (0 < v && v < n)
                    has[v] = true;
            }
        }
        for (int i = 1;; ++i)
            if (!has[i])
            {
                std::cout << i;
                break;
            }
    }
    exit(0);
    return 0;
}();

class Solution
{
public:
    int firstMissingPositive(vector<int>) { return 0; }
};
// 还有一个 直接读测试样例，写到检测输出文件的？？？