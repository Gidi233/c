class Solution
{
public:
    int findUnsortedSubarray(vector<int> &nums)
    {
        if (is_sorted(nums.begin(), nums.end()))
        {
            return 0;
        }
        vector<int> numsSorted(nums);
        sort(numsSorted.begin(), numsSorted.end());
        int left = 0;
        while (nums[left] == numsSorted[left])
        {
            left++;
        }
        int right = nums.size() - 1;
        while (nums[right] == numsSorted[right])
        {
            right--;
        }
        return right - left + 1;
    }
};
// 将原数组 nums排序与原数组进行比较，取最长的相同的前缀为 numsA ，取最长的相同的后缀为 numsC ，这样我们就可以取到最短的 numsB
​class Solution
{
public:
    int findUnsortedSubarray(vector<int> &nums)
    {
        int n = nums.size();
        int maxn = INT_MIN, right = -1;
        int minn = INT_MAX, left = -1;
        for (int i = 0; i < n; i++)
        {
            if (maxn > nums[i])
            {
                right = i;
            }
            else
            {
                maxn = nums[i];
            }
            if (minn < nums[n - i - 1])
            {
                left = n - i - 1;
            }
            else
            {
                minn = nums[n - i - 1];
            }
        }
        return right == -1 ? 0 : right - left + 1;
    }
};

// 双指针的思路：
// 如果有序则左右下标不会更新

// 用来找右边界的指针从左往右走，记录遇到的最大值，
// 一直往右走遇到的最后一个最大值的前一个位置就是右边界；

// 用来找左边界的指针从右往左走，记录遇到的最小值，
// 一直往左走遇到的最后一个最小值的前一个位置就是左边界。