class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int res=nums.size();
        for(auto i=nums.begin();i<nums.end();++i){
            if(*i==val){
                nums.erase(i);
                --res;
                --i;
            }
        }
        return res;
    }
};

//以上是我不用脑子用stl做的

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        int left = 0;
        for (int right = 0; right < n; right++) {
            if (nums[right] != val) {
                nums[left] = nums[right];
                left++;
            }
        }
        return left;
    }
};
//用双指针
//如果右指针指向的元素不等于val，它一定是输出数组的一个元素，我们就将右指针指向的元素复制到左指针位置，然后将左右指针同时右移；
//如果右指针指向的元素等于val，它不能在输出数组里，此时左指针不动，右指针右移一位。

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size();
        while (left < right) {
            if (nums[left] == val) {
                nums[left] = nums[right - 1];
                right--;
            } else {
                left++;
            }
        }
        return left;
    }
};

//这样的方法两个指针在最坏的情况下合起来只遍历了数组一次。与方法一不同的是，方法二避免了需要保留的元素的重复赋值操作。