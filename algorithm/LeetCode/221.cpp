class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size(), ans = 0;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
      if (matrix[i][0] == '1') {
        dp[i][0] = 1;
        ans = 1;
      }
    }
    for (int j = 0; j < n; j++) {
      if (matrix[0][j] == '1') {
        dp[0][j] = 1;
        ans = 1;
      }
    }
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (matrix[i][j] == '1') {
          int min_ = min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
          dp[i][j] = min_ + 1;
          ans = max(ans, dp[i][j]);
        }
      }
    }
    return ans * ans;
  }
};
// 动态规划 取当前为1的值 min(上, 左, 左上) + 1