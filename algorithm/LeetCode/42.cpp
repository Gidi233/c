class Solution
{
public:
    int trap(vector<int> &height)
    {
        int max = 0, max_i = 0;
        int slow = 0, fast = 0, ans = 0;
        for (int fast = 0; fast < height.size(); fast++)
        {
            if (height[fast] >= max)
            {
                while (slow < fast)
                {
                    ans += max - height[slow++];
                }
                max = height[fast];
                max_i = fast;
            }
        }
        slow = height.size() - 1;
        max = 0;
        for (int fast = height.size() - 1; fast >= max_i; fast--)
        {
            if (height[fast] >= max)
            {
                while (slow > fast)
                {
                    ans += max - height[slow--];
                }
                max = height[fast];
            }
        }
        return ans;
    }
};
// 快慢指针，快指针找到更高的位置，慢指针以当前值为最高值加过去

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        if (n == 0)
        {
            return 0;
        }
        vector<int> leftMax(n);
        leftMax[0] = height[0];
        for (int i = 1; i < n; ++i)
        {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }

        vector<int> rightMax(n);
        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i)
        {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans += min(leftMax[i], rightMax[i]) - height[i];
        }
        return ans;
    }
};
// 动态规划 正反遍历两次得到每个位置两边的最大高度，然后遍历取min(leftMax[i], rightMax[i]) - height[i];加和。

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int ans = 0;
        stack<int> stk;
        int n = height.size();
        for (int i = 0; i < n; ++i)
        {
            while (!stk.empty() && height[i] > height[stk.top()])
            {
                int top = stk.top();
                stk.pop();
                if (stk.empty())
                {
                    break;
                }
                int left = stk.top();
                int currWidth = i - left - 1;
                int currHeight = min(height[left], height[i]) - height[top];
                ans += currWidth * currHeight;
            }
            stk.push(i);
        }
        return ans;
    }
};
// 单调栈 栈里存储每个左边界（每个降序的墙），每当遍历到当前值大于栈顶，先弹出top（用于后面计算深度），再取此时栈顶left作为左侧的边界，把这一方形区域算出加入ans，再把当前点加入栈（作为边界、区域高度）

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right)
        {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (height[left] < height[right])
            {
                ans += leftMax - height[left];
                ++left;
            }
            else
            {
                ans += rightMax - height[right];
                --right;
            }
        }
        return ans;
    }
};
// 官方双指针，我的是先正序再逆序，官方是不断从两侧逼近，更新左右最大值，得到每个位置与对应max的差值