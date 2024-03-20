class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    return nums[nums.size() / 2];
  }
};
// 因为超过一半，所以排序后的中位数一定是众数

class Solution {
  int count_in_range(vector<int>& nums, int target, int lo, int hi) {
    int count = 0;
    for (int i = lo; i <= hi; ++i)
      if (nums[i] == target) ++count;
    return count;
  }
  int majority_element_rec(vector<int>& nums, int lo, int hi) {
    if (lo == hi) return nums[lo];
    int mid = (lo + hi) / 2;
    int left_majority = majority_element_rec(nums, lo, mid);
    int right_majority = majority_element_rec(nums, mid + 1, hi);
    if (left_majority == right_majority) return left_majority;
    if (count_in_range(nums, left_majority, lo, hi) > (hi - lo + 1) / 2)
      return left_majority;
    else
      return right_majority;
  }

 public:
  int majorityElement(vector<int>& nums) {
    return majority_element_rec(nums, 0, nums.size() - 1);
  }
};
// 分治 分成两半一定是其中一半的众数

class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    int candidate = -1;
    int count = 0;
    for (int num : nums) {
      if (num == candidate)
        ++count;
      else if (--count < 0) {
        candidate = num;
        count = 1;
      }
    }
    return candidate;
  }
};
// 最坏的情况 除了众数，其他数都相等，众数的count也更大。如果还有其他不同的数，他们之间的count也在相互抵消，所以众数的count最大