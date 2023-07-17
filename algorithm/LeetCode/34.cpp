class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n=nums.size()-1;
        if(n==-1||nums[0]>target||nums[n]<target) return {-1,-1};
        int l=0,r=n;
        int mid=(l+r)/2;
        while(l<r){
            mid=(l+r)/2;
            if(nums[mid]<target) l=mid+1;
            else r=mid;
        }
        if(nums[l]!=target) return {-1,-1};

        int left,right,mid1=l;//target的下标
        l=0,r=mid1;
        while(l<r){//左
            mid=(l+r)/2;
            if(nums[mid]<target) l=mid+1;
            else r=mid;
        }
        left=l;

        l=mid1,r=n;
        while(l<r){//右
            mid=(l+r+1)/2;
            if(nums[mid]>target) r=mid-1;
            else l=mid;
        }
        right=l;
        return {left,right};
    }
};

//二分 条件为从右向左逼近时，mid=(l+r+1)/2;
// 不用先找有没有target？？判断nums[l]==target

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
      auto it = equal_range(nums.begin(), nums.end(), target);
      vector<int> result(2, -1);
      if (it.first == it.second) return result;

      result[0] = distance(nums.begin(), it.first);
      result[1] = distance(nums.begin(), it.second) -1;
      return result;
    }
};

//一个用stl的