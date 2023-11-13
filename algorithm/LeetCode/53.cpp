
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int sum = INT_MIN, ans = INT_MIN;
        bool flag = 0;
        for (int i : nums)
        {
            if (flag)
            {
                sum += i;
                if (sum <= 0)
                {
                    flag = 0;
                    continue;
                }
            }
            if (!flag)
            {
                sum = i;
                if (i > 0)
                    flag = 1;
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
// 滚动数组

