class Solution {
public:
    int singleNumber(vector<int>& nums) {
        set<int> sets;
        for(int i=0;i<nums.size();i++){
            if(sets.find(nums[i])==sets.end()){
                sets.emplace(nums[i]);
            }
            else{
                sets.erase(nums[i]);
            }
        }
        return *(sets.begin());
    }
};

//用STL库很容易实现，但都需要额外使用 O(n) 的空间

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ret = 0;
        for (auto e: nums) ret ^= e;
        return ret;
    }
};

//位运算
//异或运算满足交换律和结合律，即 a⊕b⊕a=b⊕a⊕a=b⊕(a⊕a)=b⊕0=b
//所以把所有的数 ^运算出现两遍的就相互抵消了，最后剩下的就是只出现了一次的。