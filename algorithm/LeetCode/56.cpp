
class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<int> arr(1e4 + 1, 0);
        vector<bool> flag(1e4 + 1, 0);
        for (int i = 0; i < intervals.size(); i++)
        {
            if (intervals[i][0] == intervals[i][1])
            {
                flag[intervals[i][0]] = true;
                continue;
            }
            arr[intervals[i][0]]++;
            arr[intervals[i][1]]--;
        }
        int tmp = 0;
        vector<int> tmp_arr;
        vector<vector<int>> ans;
        for (int i = 0; i < arr.size(); i++)
        {
            if (!arr[i])
            {
                if (flag[i] && !tmp)
                    ans.push_back({i, i});
                continue;
            }
            if (arr[i] > 0 && !tmp)
                tmp_arr.push_back(i);
            tmp += arr[i];
            if (!tmp)
            {
                tmp_arr.push_back(i);
                ans.push_back(tmp_arr);
                tmp_arr.clear();
            }
        }
        return ans;
    }
};
// 差分数组 按理说是O(n)的时间复杂度，不知道为什么没官方nlogn跑得快

class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        if (intervals.size() == 0)
        {
            return {};
        }
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        for (int i = 0; i < intervals.size(); ++i)
        {
            int L = intervals[i][0], R = intervals[i][1];
            if (!merged.size() || merged.back()[1] < L)
            {
                merged.push_back({L, R});
            }
            else
            {
                merged.back()[1] = max(merged.back()[1], R);
            }
        }
        return merged;
    }
};
// 排序后
// 如果当前区间的左端点在数组 merged 中最后一个区间的右端点之后，那么它们不会重合，我们可以直接将这个区间加入数组 merged 的末尾；
// 否则，它们重合，我们需要用当前区间的右端点更新数组 merged 中最后一个区间的右端点，将其置为二者的较大值。

