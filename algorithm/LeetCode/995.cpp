class Solution
{
public:
    int minKBitFlips(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> diff(n + 1);
        int ans = 0, revCnt = 0;
        // for (int i = 0; i < n; ++i) {
        //     revCnt += diff[i];
        //     if ((nums[i] + revCnt) % 2 == 0) {
        //         if (i + k > n) {
        //             return -1;
        //         }
        //         ++ans;
        //         ++revCnt;
        //         --diff[i + k];
        //     }
        // }这个更直观
        for (int i = 0; i < n; ++i)
        {
            revCnt ^= diff[i];
            if (nums[i] == revCnt)
            { // nums[i] ^ revCnt == 0
                if (i + k > n)
                {
                    return -1;
                }
                ++ans;
                revCnt ^= 1;
                diff[i + k] ^= 1;
            }
        } // 因为只用判断奇偶，所以不用加减，用^同为奇偶时为偶要翻转，一奇一偶时不变（而且diff也只会变一次）
        return ans;
    }
};
// 差分数组（不记录具体每一位的值，记录连续区域的变化，改变的时间复杂度为O(1)，在遍历时根据记录的变化获得该值）
// 对于若干个 k 位翻转操作，改变先后顺序并不影响最终翻转的结果。
// 从左到右地执行这些翻转操作。由于翻转操作是唯一的，若最终数组元素均为 1，则执行的翻转次数就是最小的。
// 若i+k>n则无法执行翻转操作，此时应返回 −1。

class Solution
{
public:
    int minKBitFlips(vector<int> &nums, int k)
    {
        int n = nums.size();
        int ans = 0, revCnt = 0;
        for (int i = 0; i < n; ++i)
        {
            if (i >= k && nums[i - k] > 1)
            { // 判断之前有没有翻转
                revCnt ^= 1;
                nums[i - k] -= 2; // 复原数组元素，若允许修改数组 nums，则可以省略
            }
            if (nums[i] == revCnt)
            {
                if (i + k > n)
                {
                    return -1;
                }
                ++ans;
                revCnt ^= 1;
                nums[i] += 2;
            }
        }
        return ans;
    }
};
// 滑动窗口（双指针）
//  因为0≤nums[i]≤1，我们可以用 nums[i] 范围之外的数来表达「是否翻转过」的含义。就不用建一个差分数组了
//  即若要翻转从位置 i 开始的子数组，可以将 nums[i] 加 2。
