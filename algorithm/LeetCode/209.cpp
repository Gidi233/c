class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int l = 0, r = 0, sum = 0, ans = nums.size();
        bool flag = 1;
        while (1)
        {
            if (sum < target)
            {
                if (r == nums.size())
                    break;
                sum += nums[r++];
            }
            else
            {
                ans = min(ans, r - l);
                flag = 0;
                sum -= nums[l++];
            }
        }
        if (flag)
            return 0;
        return ans;
    }
};
// 滑动窗口

class Solution
{
public:
    int minSubArrayLen(int s, vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
        {
            return 0;
        }
        int ans = INT_MAX;
        vector<int> sums(n + 1, 0);
        // 为了方便计算，令 size = n + 1
        // sums[0] = 0 意味着前 0 个元素的前缀和为 0
        // sums[1] = A[0] 前 1 个元素的前缀和为 A[0]
        // 以此类推
        for (int i = 1; i <= n; i++)
        {
            sums[i] = sums[i - 1] + nums[i - 1];
        }
        for (int i = 1; i <= n; i++)
        {
            int target = s + sums[i - 1];
            auto bound = lower_bound(sums.begin(), sums.end(), target);
            if (bound != sums.end())
            {
                ans = min(ans, static_cast<int>((bound - sums.begin()) - (i - 1)));
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};
// 前缀和 + 二分查找