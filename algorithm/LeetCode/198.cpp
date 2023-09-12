// class Solution {
//     private:
//     int dp(vector<int>& nums,int index){
//         if(index+3>size){
//             if(index+2==size)
//             return nums[index]+dp(nums,index+2);
//             else return nums[index];
//         }
//         else
//         return max(nums[index]+dp(nums,index+2),nums[index]+dp(nums,index+3));
//     }
//     int size;
// public:
//     int rob(vector<int>& nums) {
//         size=nums.size()-1;
//         int ans=max(dp(nums,0),dp(nums,1));
//         return ans;

//     }
// };
// 不行，数据量大的话直接爆栈，且超时

// class Solution {
// public:
//     int rob(vector<int>& nums) {
//         int size=nums.size();
//     vector<int> db(size);
//     if(size==1) return nums[0];
//     for(int i=0;i<size;i++){
//         if(i<2){
//             db[i]=nums[i];
//             continue;
//         }
//         if(i==2){
//             db[i]=nums[i]+db[0];
//             continue;
//         }
//         db[i]=nums[i]+max(db[i-2],db[i-3]);
//     }
//     return max(db[size-1],db[size-2]);

//     }
// };
// 动态规划

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        if (nums.empty())
        {
            return 0;
        }
        int size = nums.size();
        if (size == 1)
        {
            return nums[0];
        }
        int first = nums[0], second = max(nums[0], nums[1]);
        for (int i = 2; i < size; i++)
        {
            int temp = second;
            second = max(first + nums[i], second);
            first = temp;
        }
        return second;
    }
};

// 考虑到每间房屋的最高总金额只和该房屋的前两间房屋的最高总金额相关，因此可以使用滚动数组，在每个时刻只需要存储前两间房屋的最高总金额。