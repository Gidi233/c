class Solution {
public:
    vector<int> intersection(vector<vector<int>>& nums) {
        vector<int> result;
        map<int, int> map;
        /* 记录每个数的出现次数 */
        for (vector<int>& num: nums) 
            for (int x: num) map[x]++;

        /* 某个数出现次数等于数组个数，代表它在所有数组中都出现过 */
        for (pair<int, int> iter: map)
            if (iter.second == nums.size())
                result.push_back(iter.first);

        return result;
    }
};

//因为一个数组不会出现重复数，所以遍历完加起来等于数组数的即为所求。


class Solution {
public:
    vector<int> hashsetmethod(vector<vector<int>>& arrs) {
        set<int> hashSet;
        for(auto& arr : arrs[0])
            hashSet.insert(arr);
        for(int i = 1; i < arrs.size(); i++) {
            set<int> tmpSet;
            for(auto& arr : arrs[i])
                if (hashSet.count(arr))  tmpSet.insert(arr);
            hashSet = tmpSet;
            if(hashSet.empty()) return {};
        }
        return vector<int>(hashSet.begin(), hashSet.end());;
    }
public:
    vector<int> intersection(vector<vector<int>>& nums) {
        return hashsetmethod(nums);
    }
};     

//先把第一个数组记录，然后循环保留与下一个数组相同的数据，遍历完即为所求。


class Solution {
public:
    /* 求两个数组的交集 */
    vector<int> intersectionOfTwoArrays(vector<int> nums1, vector<int> nums2) {
        if (nums1.size() == 0 || nums2.size() == 0) return {}; 
        /* 存放结果 */
        unordered_set<int> result_set; 
        unordered_set<int> nums_set(nums1.begin(), nums1.end());
        for (int num : nums2)
            /* 发现nums2的元素 在nums_set里又出现过 */
            if (nums_set.find(num) != nums_set.end())
                result_set.insert(num);
        return vector<int>(result_set.begin(), result_set.end());
    }
    vector<int> recursionmethod(vector<vector<int>>& arrs, int start, int end) {
        /* 递归截止条件 */
        if (start == end) return arrs[start];
        /* 递归中间处理逻辑 */
        int mid = start + (end - start) / 2;
        vector<int> left = recursionmethod(arrs, start, mid);
        vector<int> right = recursionmethod(arrs, mid + 1, end);
        return intersectionOfTwoArrays(left, right); 
    }
public:

    vector<int> intersection(vector<vector<int>>& nums) {
        vector<int> result = recursionmethod(nums,0,nums.size()-1);
        sort(result.begin(),result.end());
        return result;
    }
};

//跟上一个方法差不多，用递归把每个相邻数组的相同元素提取，把提取出来的再提取相同元素
//因为没有重复数，应该不用用unorder_set,直接用vector迭代器find，最后再排序