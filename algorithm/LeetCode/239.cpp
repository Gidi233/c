class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        priority_queue<pair<int, int>> q;
        for (int i = 0; i < k; ++i)
        {
            q.emplace(nums[i], i);
        }
        vector<int> ans = {q.top().first};
        for (int i = k; i < n; ++i)
        {
            q.emplace(nums[i], i);
            while (q.top().second <= i - k)
            {
                q.pop();
            }
            ans.push_back(q.top().first);
        }
        return ans;
    }
};
// 优先队列 时间复杂度：O(nlog⁡n)   空间复杂度：O(n)
class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        deque<int> q;
        for (int i = 0; i < k; ++i)
        {
            while (!q.empty() && nums[i] >= nums[q.back()])
            {
                q.pop_back();
            }
            q.push_back(i);
        }

        vector<int> ans = {nums[q.front()]};
        for (int i = k; i < n; ++i)
        {
            while (!q.empty() && nums[i] >= nums[q.back()])//遇到大的数字就把小的清掉
            {
                q.pop_back();
            }
            q.push_back(i);
            if (q.front() <= i - k) // 此时的最大值可能在滑动窗口左边界的左侧，并且随着窗口向右移动，它永远不可能出现在滑动窗口中了。因此我们还需要不断从队首弹出元素，直到队首元素在窗口中为止。
            {
                q.pop_front();
            }
            ans.push_back(nums[q.front()]);
        }
        return ans;
    }
};
// 单调队列 队头为窗口中最大值，队头到队尾严格递减

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> prefixMax(n), suffixMax(n);
        for (int i = 0; i < n; ++i)
        {
            if (i % k == 0)
            {
                prefixMax[i] = nums[i];
            }
            else
            {
                prefixMax[i] = max(prefixMax[i - 1], nums[i]);
            }
        }
        for (int i = n - 1; i >= 0; --i)
        {
            if (i == n - 1 || (i + 1) % k == 0)
            {
                suffixMax[i] = nums[i];
            }
            else
            {
                suffixMax[i] = max(suffixMax[i + 1], nums[i]);
            }
        }

        vector<int> ans;
        for (int i = 0; i <= n - k; ++i)
        {
            ans.push_back(max(suffixMax[i], prefixMax[i + k - 1]));
        }
        return ans;
    }
};
// 分块 + 预处理（动态规划）