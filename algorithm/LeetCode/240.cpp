
// 想了一个不知道怎么实现，
// 1.在斜角（左上右下）二分，判断找出的是不是target
// 2.排除左上角右下角两个方块
// 3.在剩下的区域重复1（传入两个pair 剩余区域左上右下两个坐标?一直递归），直到找完

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while (x < m && y >= 0)
        {
            if (matrix[x][y] == target)
            {
                return true;
            }
            if (matrix[x][y] > target)
            {
                --y;
            }
            else
            {
                ++x;
            }
        }
        return false;
    }
};
// 取右上角 一个行最大 一个列最小，列中最小大于target左移（减小），行中最大小于target下移（增大）