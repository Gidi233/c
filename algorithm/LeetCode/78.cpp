class Solution
{
public:
    vector<int> t;
    vector<vector<int>> ans;

    vector<vector<int>> subsets(vector<int> &nums)
    {
        int n = nums.size();
        for (int mask = 0; mask < (1 << n); ++mask)
        {
            t.clear();
            for (int i = 0; i < n; ++i)
            {
                if (mask & (1 << i))
                {
                    t.push_back(nums[i]);
                }
            }
            ans.push_back(t);
        }
        return ans;
    }
};
// 迭代 用二进制位来代表每个数字出现的情况
class Solution
{
public:
    vector<int> t;
    vector<vector<int>> ans;

    void dfs(int cur, vector<int> &nums)
    {
        if (cur == nums.size())
        {
            ans.push_back(t);
            return;
        }
        t.push_back(nums[cur]);
        dfs(cur + 1, nums);
        t.pop_back();
        dfs(cur + 1, nums);
    }

    vector<vector<int>> subsets(vector<int> &nums)
    {
        dfs(0, nums);
        return ans;
    }
};
// 递归 在每一个下标选取这一位或跳过

class Solution
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> lists;      // 解集
        lists.push_back(vector<int>()); // 首先将空集加入解集中
        for (int i = 0; i < nums.size(); i++)
        {
            int size = lists.size(); // 当前子集数
            for (int j = 0; j < size; j++)
            {
                vector<int> newList = lists[j]; // 拷贝所有子集
                newList.push_back(nums[i]);     // 向拷贝的子集中加入当前数形成新的子集
                lists.push_back(newList);       // 向lists中加入新子集
            }
        }
        return lists;
    }
};
// 动态规划 在所有答案中加上当前数