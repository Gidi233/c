class Solution
{
public:
    void func(vector<vector<int>> &m, int s)
    {
        if (s == m.size())
            return;

        int x = m.size() - s - 1;
        for (int i = s; i <= x - 1; i++)
        {
            int tmp = m[s][i];
            swap(tmp, m[i][x]);
            swap(tmp, m[x][x - i + s]);
            swap(tmp, m[x - i + s][s]);
            swap(tmp, m[s][i]);
        }
        func(m, s + 1);
    }
    void rotate(vector<vector<int>> &matrix)
    {
        func(matrix, 0);
    }
};
// 逻辑不顺 算是半试半推出来的 一圈一圈从外往里互换
class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        // C++ 这里的 = 拷贝是值拷贝，会得到一个新的数组
        auto matrix_new = matrix;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                matrix_new[j][n - i - 1] = matrix[i][j];
            }
        }
        // 这里也是值拷贝
        matrix = matrix_new;
    }
};
// 用辅助数组，把第一行放到最后一列 以此类推
class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        // 水平翻转
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                swap(matrix[i][j], matrix[n - i - 1][j]);
            }
        }
        // 主对角线翻转
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};
// 见上