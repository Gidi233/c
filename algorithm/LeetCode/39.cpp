#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    vector<vector<int>> ans;
    void func(vector<int> &c, vector<int> &tmp, int index, int target)
    {
        if (target == 0){
            ans.push_back(tmp);
            return ;
        }
        while (1)
        {
            index = upper_bound(c.begin(), c.begin() + index, target) - c.begin();
            if (index == 0)
                break;
            int num = target - c[index - 1];
            tmp.push_back(c[index - 1]);
            func(c, tmp, index, num);
            tmp.pop_back();
            index--;
        }
        return ;
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        vector<int> i;
        func(candidates, i, candidates.size(), target);
        return ans;
    }
};
// 回溯 先排序 再用二分（想找出第一个小于等于，要反向排序传进去greater<int>()），避免了n平方的遍历