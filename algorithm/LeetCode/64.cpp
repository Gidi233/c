#include <bits/stdc++.h>
using namespace std;
class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    for (int j = 0; j < n; j++) {
      if (j) grid[0][j] += grid[0][j - 1];
    }
    for (int i = 1; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (!j)
          grid[i][j] += grid[i - 1][j];
        else
          grid[i][j] += min(grid[i][j - 1], grid[i - 1][j]);
      }
    }
    return grid[m - 1][n - 1];
  }
};
  int main() { Solution solution; }