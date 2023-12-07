class Solution
{
public:
    vector<int> ans;

    void circle(const vector<vector<int>> &matrix, int l, int r, int u, int d)
    {
        if (r == l || u == d)
            return;
        if (r - l == 1)
        {
            for (int i = u; i < d; i++)
                ans.push_back(matrix[i][l]);
            return;
        }
        if (d - u == 1)
        {
            for (int i = l; i < r; i++)
                ans.push_back(matrix[u][i]);
            return;
        }
        for (int i = l; i < r - 1; i++)
            ans.push_back(matrix[u][i]);
        for (int i = u; i < d - 1; i++)
            ans.push_back(matrix[i][r - 1]);
        for (int i = r - 1; i >= l + 1; i--)
            ans.push_back(matrix[d - 1][i]);
        for (int i = d - 1; i >= u + 1; i--)
            ans.push_back(matrix[i][l]);
        circle(matrix, l + 1, r - 1, u + 1, d - 1);
    }

    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        ans.clear();
        circle(matrix, 0, matrix[0].size(), 0, matrix.size());
        return ans;
    }
};
// 按层遍历、模拟

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }

        int rows = matrix.size(), columns = matrix[0].size();
        vector<int> order;
        int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; column++) {
                order.push_back(matrix[top][column]);
            }
            for (int row = top + 1; row <= bottom; row++) {
                order.push_back(matrix[row][right]);
            }
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) {
                    order.push_back(matrix[bottom][column]);
                }
                for (int row = bottom; row > top; row--) {
                    order.push_back(matrix[row][left]);
                }
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return order;
    }
};
// 官方按层遍历，非递归

class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        res = []
        while matrix:
            res += matrix.pop(0)
            matrix = list(zip(*matrix))[::-1]
        return res
// 一个神奇的Python解法，先转置，再上下翻转
