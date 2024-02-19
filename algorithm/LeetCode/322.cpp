class Solution
{
    vector<int> count;
    int dp(vector<int> &coins, int rem)
    {
        if (rem < 0)
            return -1;
        if (rem == 0)
            return 0;
        if (count[rem - 1] != 0)
            return count[rem - 1];
        int Min = INT_MAX;
        for (int coin : coins)
        {
            int res = dp(coins, rem - coin);
            if (res >= 0 && res < Min)
            {
                Min = res + 1;
            }
        }
        count[rem - 1] = Min == INT_MAX ? -1 : Min;
        return count[rem - 1];
    }

public:
    int coinChange(vector<int> &coins, int amount)
    {
        if (amount < 1)
            return 0;
        count.resize(amount);
        return dp(coins, amount);
    }
};
//  记忆化搜索，以构成前一个组成金额 i 所需最少的硬币数量推出后面金额的
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i)
        {
            for (int j = 0; j < (int)coins.size(); ++j)
            {
                if (coins[j] <= i)
                {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
// 动态规划 思想一样这个是从小往大推。是一个是从大往小遍历
