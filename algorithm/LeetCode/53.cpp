class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int sum = INT_MIN, ans = INT_MIN;
        bool flag = 0;
        for (int i : nums)
        {
            if (flag)
            {
                sum += i;
                if (sum <= 0)
                {
                    flag = 0;
                    continue;
                }
            }
            if (!flag)
            {
                sum = i;
                if (i > 0)
                    flag = 1;
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
// 滚动数组

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int pre = 0, maxAns = nums[0];
        for (const auto &x : nums)
        {
            pre = max(pre + x, x); // 动态规划转移方程
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};
// 官答 简洁

class Solution
{
public:
    struct Status
    {
        int lSum, rSum, mSum, iSum;
    };

    Status pushUp(Status l, Status r)
    {
        int iSum = l.iSum + r.iSum;
        int lSum = max(l.lSum, l.iSum + r.lSum);
        int rSum = max(r.rSum, r.iSum + l.rSum);
        int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
        return (Status){lSum, rSum, mSum, iSum};
    };

    Status get(vector<int> &a, int l, int r)
    {
        if (l == r)
        {
            return (Status){a[l], a[l], a[l], a[l]};
        }
        int m = (l + r) >> 1;
        Status lSub = get(a, l, m);
        Status rSub = get(a, m + 1, r);
        return pushUp(lSub, rSub);
    }

    int maxSubArray(vector<int> &nums)
    {
        return get(nums, 0, nums.size() - 1).mSum;
    }
};
// 线段树 分治