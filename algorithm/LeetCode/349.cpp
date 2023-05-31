
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        unordered_set<int> us{ nums1.begin(), nums1.end() };
        for (auto& i : nums2) {
            if (us.find(i) != us.end()) {
                us.erase(i);
                ans.emplace_back(i);
            }
        }
        return ans;
    }
};
//函数STL了解不多啊
//unordered_set底层用的是哈希表结构查找的时间复杂度只有O(1) （去重，无序），然后遍历找一遍就行。
//或者排序，两个指针遍历一遍把相同的加到数组。

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int length1 = nums1.size(), length2 = nums2.size();
        int index1 = 0, index2 = 0;
        vector<int> intersection;
        while (index1 < length1 && index2 < length2) {
            int num1 = nums1[index1], num2 = nums2[index2];
            if (num1 == num2) {
                // 保证加入元素的唯一性
                if (!intersection.size() || num1 != intersection.back()) {
                    intersection.push_back(num1);
                }
                index1++;
                index2++;
            } else if (num1 < num2) {
                index1++;
            } else {
                index2++;
            }
        }
        return intersection;
    }
};