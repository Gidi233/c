#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int r = nums.size() - 1, l = 0, last = nums[l], mid;
        while (1)
        {
            mid = (l + r) / 2;
            if (l == r || nums[mid] > nums[mid + 1])
                break;
            if (nums[mid] >= last)
            {
                l = mid + 1;
                last = nums[mid + 1];
            }
            else
            {
                r = mid;
                last = nums[mid];
            }
        }
        if (target < nums[0])
        {
            auto i = lower_bound(nums.begin() + mid + 1, nums.end(), target);
            if (i == nums.end())
                return -1;
            if (*i == target)
                return i - nums.begin();
            else
                return -1;
        }
        if (target == nums[0])
        {
            return 0;
        }
        if (target > nums[0])
        {
            auto i = lower_bound(nums.begin(), nums.begin() + mid, target);
            if (i == nums.end())
                return -1;
            if (*i == target)
                return i - nums.begin();
            else
                return -1;
        }
    }
};
// 二分 在找二分的临界条件时还是有点问题，多花了点时间。
// 先找到临界的点然后，通过target的大小在其中一边二分。

class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int n = (int)nums.size();
        if (!n)
        {
            return -1;
        }
        if (n == 1)
        {
            return nums[0] == target ? 0 : -1;
        }
        int l = 0, r = n - 1;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[0] <= nums[mid])
            {
                if (nums[0] <= target && target < nums[mid])
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            else
            {
                if (nums[mid] < target && target <= nums[n - 1])
                {
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};
// 官方的二分
// 在有序的序列里找target，不存在则改变左右边界
// 定理一：只有在顺序区间内才可以通过区间两端的数值判断target是否在其中。
//
// 定理二：判断顺序区间还是乱序区间，只需要对比 left 和 right 是否是顺序对即可，left <= right，顺序区间，否则乱序区间。
//
//  定理三：每次二分都会至少存在一个顺序区间。