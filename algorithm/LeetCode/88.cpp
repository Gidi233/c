#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        vector<int> ans(m + n);
        int i1 = 0, i2 = 0;
        while (i1 < m && i2 < n)
        {
            if (nums1[i1] < nums2[i2])
            {
                ans[i1 + i2] = nums1[i1];
                i1++;
            }
            else
            {
                ans[i1 + i2] = nums2[i2];
                i2++;
            }
        }
        // if(i1==m&&i2==n)
        //     return;
        if (i1 == m)
            while (i2 < n)
            {
                ans[i1 + i2] = nums2[i2];
                i2++;
            }
        else
            while (i1 < m)
            {
                ans[i1 + i2] = nums1[i1];
                i1++;
            }
        nums1 = ans;
    }
};

// 双指针
class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int p1 = m - 1, p2 = n - 1, p = m + n - 1;
        while (p2 >= 0)
        { // nums2 还有要合并的元素
            // 如果 p1 < 0，那么走 else 分支，把 nums2 合并到 nums1 中
            if (p1 >= 0 && nums1[p1] > nums2[p2])
            {
                nums1[p--] = nums1[p1--]; // 填入 nums1[p1]
            }
            else
            {
                nums1[p--] = nums2[p2--]; // 填入 nums2[p1]
            }
        }
    }
};
//逆向双指针，就不用开那个数组了

int main()
{
    Solution solution;
}