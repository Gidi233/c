class Solution
{
public:
    bool flag[6]; // bool是一字节吗，可以换成状态压缩
    vector<vector<int>> ans;
    void dfs(vector<int> &nums, vector<int> tmp)
    {
        if (tmp.size() == nums.size())
        {
            ans.emplace_back(tmp);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if (flag[i])
                continue;
            tmp.emplace_back(nums[i]);
            flag[i] = 1;
            dfs(nums, tmp);
            flag[i] = 0;
            tmp.pop_back();
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        ans.clear();
        memset(flag, 0, sizeof(flag));
        vector<int> tmp;
        dfs(nums, tmp);
        return ans;
    }
};
// 回溯，递归
class Solution
{
public:
    void backtrack(vector<vector<int>> &res, vector<int> &output, int first, int len)
    {
        // 所有数都填完了
        if (first == len + 1)
        {
            res.emplace_back(output);
            return;
        }
        for (int i = first; i < len; ++i)
        {
            // 动态维护数组
            swap(output[i], output[first]);
            // 继续递归填下一个数
            backtrack(res, output, first + 1, len);
            // 撤销操作
            swap(output[i], output[first]);
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> res;
        backtrack(res, nums, 0, (int)nums.size());
        return res;
    }
};
// 官方回溯，递归
// 通过将nums分为两部分，互换已加入与待加入的数，优化掉了标记数组
