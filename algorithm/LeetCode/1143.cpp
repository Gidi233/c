class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        int m = text1.length(), n = text2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
        {
            char c1 = text1.at(i - 1);
            for (int j = 1; j <= n; j++)
            {
                char c2 = text2.at(j - 1);
                if (c1 == c2) // 状态转移方程
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};



class Solution
{
public:
    int longestCommonSubsequence(string s, string t)
    {
        int n = s.length(), m = t.length(), f[2][m + 1];
        memset(f, 0, sizeof(f));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                f[(i + 1) % 2][j + 1] = s[i] == t[j] ? f[i % 2][j] + 1 : max(f[i % 2][j + 1], f[(i + 1) % 2][j]);
        return f[n % 2][m];
    }
};
// 滚动数组 只需要dp[i][j]dp[i][j-1]dp[i-1][j]，所以可以把之前的覆盖掉