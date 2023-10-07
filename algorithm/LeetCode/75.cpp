class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int l = 0, r = nums.size() - 1;
        int i = 0;
        while (i <= r)
        {
            if (nums[i] == 0)
            {
                if (i == l)
                {
                    i++;
                    l++;
                    continue;
                }
                int temp = nums[l];
                nums[l] = nums[i];
                l++;
                nums[i] = temp;
            }
            if (nums[i] == 2)
            {
                int temp = nums[r];
                nums[r] = nums[i];
                r--;
                nums[i] = temp;
            }
            if (nums[i] == 1)
                i++;
        }
    }
};
// 双指针，分别把0往头放，2往尾放，遍历到尾指针

class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int n = nums.size();
        int p0 = 0, p1 = 0;
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] == 1)
            {
                swap(nums[i], nums[p1]);
                ++p1;
            }
            else if (nums[i] == 0)
            {
                swap(nums[i], nums[p0]);
                if (p0 < p1)
                {
                    swap(nums[i], nums[p1]);
                }
                ++p0;
                ++p1;
            }
        }
    }
};
// 双指针 两个指针分别记录0、1的位置，要重复判断1