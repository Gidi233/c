class Solution {
public:
    int countNicePairs(vector<int>& nums) {
        const int MOD = 1000000007;
        int res = 0;
        unordered_map<int, int> h;
        for (int i : nums) {
            int temp = i, j = 0;
            while (temp > 0) {
                j = j * 10 + temp % 10;
                temp /= 10;
            }
            res = (res + h[i - j]) % MOD;
            h[i - j]++;
        }
        return res;
    }
};
//用了unordered_map，用哈希表储存，搜索复杂度是O(1)
//先用式子变换，能只通过自身算出一个值进行匹配。（nums[i]+rev(nums[j])=nums[j]+rev(nums[i])）->（nums[i]−rev(nums[i])=nums[j]−rev(nums[j])）
//算出f（i）的值连加，再自增。遍历得到结果。
//f（i）=nums[i]-rev(nums[j])