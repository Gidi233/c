class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        if (numbers.size() == 2)
            return {1, 2};
        auto l = numbers.begin(), r = numbers.end(), left = numbers.begin(), right = numbers.end();
        auto m = lower_bound(l, r, target / 2); // 大于等于
        l = m;
        if (*l * 2 == target)
        {
            if (*l == *(l + 1))
                return {static_cast<int>(l - numbers.begin() + 1), static_cast<int>(l - numbers.begin() + 2)};
            r = m + 1;
        }
        else
            r = m;
        int num = *l + *r;
        while (num != target)
        {
            if (num < target)
            {
                r = lower_bound(r, right, target - *l);
            }
            else
            {
                l = upper_bound(left, l, target - *r) - 1; // 往左找小于等于目标值的位置，因为upper_bound是大于（不知道官方库里有没有小于等于），用它找到的值-1也行
            }
            num = *l + *r;
        }
        int ansl = l - numbers.begin() + 1, ansr = r - numbers.begin() + 1;
        return {ansl, ansr};
    }
};
// 二分：先找到中间，大了往左边找，小了往右找。

class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        for (int i = 0; i < numbers.size(); ++i)
        {
            int low = i + 1, high = numbers.size() - 1;
            while (low <= high)
            {
                int mid = (high - low) / 2 + low;
                if (numbers[mid] == target - numbers[i])
                {
                    return {i + 1, mid + 1};
                }
                else if (numbers[mid] > target - numbers[i])
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }
        }
        return {-1, -1};
    }
};
// 官方二分,循环固定一侧，二分找另一侧

class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        int low = 0, high = numbers.size() - 1;
        while (low < high)
        {
            int sum = numbers[low] + numbers[high];
            if (sum == target)
            {
                return {low + 1, high + 1};
            }
            else if (sum < target)
            {
                ++low;
            }
            else
            {
                --high;
            }
        }
        return {-1, -1};
    }
};
// 双指针