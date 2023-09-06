class Solution
{
public:
    int findRepeatNumber(vector<int> &nums)
    {
        unordered_map<int, bool> map;
        for (int num : nums)
        {
            if (map[num])
                return num;
            map[num] = true;
        }
        return -1;
    }
};
// 用哈希map解决

class Solution
{
public:
    int findRepeatNumber(vector<int> &nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            int k = nums[i];
            if (k < 0)
                k += n;
            if (nums[k] < 0)
                return k;
            nums[k] -= n;
        }
        return -1;
    }
};
// 一个取巧的方法（空间复杂度为O(1)）
// 将原先的数组重复利用，元素出现就将其作为下标减固定大小为负（表示已存在一个），在需要得到原数组元素时再加上固定大小（右值引用的话可以这么用吧）

class Solution
{
public:
    int findRepeatNumber(vector<int> &nums)
    {
        int i = 0;
        while (i < nums.size())
        {
            if (nums[i] == i)
            {
                i++;
                continue;
            }
            if (nums[nums[i]] == nums[i])
                return nums[i];
            swap(nums[i], nums[nums[i]]);
        }
        return -1;
    }
};
// 将元素值以下标顺序排序，如果在需要交换时发现nums[i] ==i说明已经出现过了
