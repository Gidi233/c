class Solution {
public:
    int minMoves(vector<int>& nums) {
        int n=nums.size();
        int res=0;
        sort(nums.begin(),nums.end());
        for(int i=1;i<n;i++){
            res+=nums[i]-nums[0];
        }
        return res;
    }
};
//让n-1个元素+1就等于让一个非最小值-1 ，所以找到数组中的最小值，将每个元素与最小值的差相加就是答案
//上面是我写的，不知为何比直接找到最小值内存占用少。（可能就是因为多了个储存最小值的变量吧hhh） 

class Solution {
public:
  int minMoves(vector<int> &nums) {
    
    int las = *min_element(nums.begin(), nums.end());;
    int ans = 0;
    for (int n : nums) {
      ans += n - las;
    }
    return ans;
  }
};

