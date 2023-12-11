class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = (int)nums.size();
        if (n == 0)
        {
            return 0;
        }
        vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i)
        {
            dp[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
// 动态规划 O(n^2)
// 每次都循环检查之前比当前值小的长度的最大值，设置当前长度为之前找到的最大值+1

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int len = 1, n = (int)nums.size();
        if (n == 0)
        {
            return 0;
        }
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i)
        {
            if (nums[i] > d[len])
            {
                d[++len] = nums[i];
            }
            else
            {
                int l = 1, r = len, pos = 0; // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                while (l <= r)
                {
                    int mid = (l + r) >> 1;
                    if (d[mid] < nums[i])
                    {
                        pos = mid;
                        l = mid + 1;
                    }
                    else
                    {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};
// 二分+贪心
// d[i]表示长度为 i 的最长上升子序列的末尾元素的最小值，因为d[i]是关于 i单调递增的
// 所以依次遍历数组 nums 中的每个元素，并更新数组 d 和 len 的值。如果 nums[i]> d[len] 则更新 len = len + ,并d[len]=nums[i]，否则在 d[1…len]中找满足 d[i−1]<nums[j]<d[i]的下标 i，并更新 d[i]=nums[j]
// 因为d[i]是单调递增,所以用二分把时间复杂度降到O(nlogn)

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> g;
        for (int x : nums)
        {
            auto it = lower_bound(g.begin(), g.end(), x);
            if (it == g.end())
                g.push_back(x); // >=x 的 g[j] 不存在
            else
                *it = x;
        }
        return g.size();
    }
};

class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        auto end = nums.begin();// 原地修改
        for (int x : nums)
        {
            auto it = lower_bound(nums.begin(), end, x);
            *it = x;
            if (it == end) // >=x 的 g[j] 不存在
                ++end;
        }
        return end - nums.begin();
    }
};

// 作者：灵茶山艾府
// 优雅c++使用者
// lower_bound 第一个不小于给定值的元素的迭代器 upper_bound 指向第一个大于给定值的元素的迭代器
// d/g数组存的不是结果序列
// 如果想得到子序列,需要用 n^2 DP 的写法，用一个 from 数组记录转移来源，最后从终点出发顺着 from 数组走到起点，就得到了对应的 LIS。