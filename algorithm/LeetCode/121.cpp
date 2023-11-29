class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int minn = prices[0], ans = 0;
        for (int i : prices)
        {
            if (minn > i)
                minn = i;
            else
                ans=max(ans, i - minn);
        }
        return ans;
    }
};
// 动态规划 不断更新最小值，计算差值，保留最大值
