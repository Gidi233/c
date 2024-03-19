class Solution {
 public:
  int findLength(vector<int>& A, vector<int>& B) {
    int n = A.size(), m = B.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
      for (int j = m - 1; j >= 0; j--) {
        dp[i][j] = A[i] == B[j] ? dp[i + 1][j + 1] + 1 : 0;
        ans = max(ans, dp[i][j]);
      }
    }
    return ans;
  }
};
// 动态规划 从后往前推(从前往后都可以)  利用之前以重复的
class Solution {
 public:
  int maxLength(vector<int>& A, vector<int>& B, int addA, int addB, int len) {
    int ret = 0, k = 0;
    for (int i = 0; i < len; i++) {
      if (A[addA + i] == B[addB + i]) {
        k++;
      } else {
        k = 0;
      }
      ret = max(ret, k);
    }
    return ret;
  }
  int findLength(vector<int>& A, vector<int>& B) {
    int n = A.size(), m = B.size();
    int ret = 0;
    for (int i = 0; i < n; i++) {
      int len = min(m, n - i);
      int maxlen = maxLength(A, B, i, 0, len);
      ret = max(ret, maxlen);
    }
    for (int i = 0; i < m; i++) {
      int len = min(n, m - i);
      int maxlen = maxLength(A, B, 0, i, len);
      ret = max(ret, maxlen);
    }
    return ret;
  }
};
// 滑动窗口找到所有的对齐方式，（暴力就是把相同对齐方式下不同下标的重复计算了），在计算每种对齐方式下的最长重复字串

class Solution {
 public:
  const int mod = 1000000009;
  const int base = 113;

  // 使用快速幂计算 x^n % mod 的值
  long long qPow(long long x, long long n) {
    long long ret = 1;
    while (n) {
      if (n & 1) {
        ret = ret * x % mod;
      }
      x = x * x % mod;
      n >>= 1;
    }
    return ret;
  }

  bool check(vector<int>& A, vector<int>& B, int len) {
    long long hashA = 0;
    for (int i = 0; i < len; i++) {
      hashA = (hashA * base + A[i]) % mod;
    }
    unordered_set<long long> bucketA;
    bucketA.insert(hashA);
    long long mult = qPow(base, len - 1);
    for (int i = len; i < A.size(); i++) {
      hashA =
          ((hashA - A[i - len] * mult % mod + mod) % mod * base + A[i]) % mod;
      bucketA.insert(hashA);
    }
    long long hashB = 0;
    for (int i = 0; i < len; i++) {
      hashB = (hashB * base + B[i]) % mod;
    }
    if (bucketA.count(hashB)) {
      return true;
    }
    for (int i = len; i < B.size(); i++) {
      hashB =
          ((hashB - B[i - len] * mult % mod + mod) % mod * base + B[i]) % mod;
      if (bucketA.count(hashB)) {
        return true;
      }
    }
    return false;
  }

  int findLength(vector<int>& A, vector<int>& B) {
    int left = 1, right = min(A.size(), B.size()) + 1;
    while (left < right) {
      int mid = (left + right) >> 1;
      if (check(A, B, mid)) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    return left - 1;
  }
};
// 把每一个长度子串做hash