class Solution {

public:

    int longestArithSeqLength(vector<int> &a) {

        int ans = 0, n = a.size(), f[n][1001];

        memset(f, 0, sizeof(f));

        for (int i = 1; i < n; ++i)

            for (int j = i - 1; j >= 0; --j) {

                int d = a[i] - a[j] + 500; // +500 防止出现负数

                if (f[i][d] == 0) {

                    f[i][d] = f[j][d] + 1; // 默认的 1 在下面返回时加上

                    ans = max(ans, f[i][d]);

                }

            }

        return ans + 1;

    }

};
//dp线性规划 n是给定的数据多少 1001是差值（因为数据大小是0——500,所以差值是正负500），数组的值是等差数列长度，
//第二个循环从右往左 因为就贪心思想 从右寻找 左边可以有更多的作为等差的数。（否则得遍历维护最大值）