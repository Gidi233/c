#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    string multiply(string num1, string num2)
    {
        if (num1 == "0" || num2 == "0")
            return "0";
        string ans;
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        for (int i1 = 0; i1 < num1.size(); i1++)
        {
            for (int i2 = 0; i2 < num2.size(); i2++)
            {
                bool flag = ans.size() == i2 + i1;
                int last = flag ? 0 : ans[i2 + i1];
                int t = (num1[i1] - '0') * (num2[i2] - '0');
                int carry = t / 10;
                if (flag)
                    ans += t % 10;
                else
                    ans[i1 + i2] += t % 10;
                if (ans[i1 + i2] > 9)
                {
                    carry += ans[i1 + i2] / 10;
                    ans[i1 + i2] %= 10;
                }
                // if (ans[i1 + i2] > 9)//会进2 所以不行 （本位的两个9 前一位进一个9）
                // {
                //     ans[i1 + i2] -= 10;
                //     carry++;
                // }
                if (carry)
                {
                    if (flag || ans.size() == i1 + i2 + 1)
                        ans += carry;
                    else
                        ans[i1 + i2 + 1] += carry;
                }
            }
        }
        if (ans[ans.size() - 1] > 9)
        {
            ans[ans.size() - 1] %= 10;
            ans += 1;
            // ans.append(1,char(1));
            // ans.push_back(1);
        }
        for (char &i : ans)
            i += '0';

        reverse(ans.begin(), ans.end());
        return ans;
    }
};
// 模拟每一位乘完另一个字符串后相加
class Solution
{
public:
    string multiply(string num1, string num2)
    {
        if (num1 == "0" || num2 == "0")
        {
            return "0";
        }
        int m = num1.size(), n = num2.size();
        auto ansArr = vector<int>(m + n);
        for (int i = m - 1; i >= 0; i--)
        {
            int x = num1.at(i) - '0';
            for (int j = n - 1; j >= 0; j--)
            {
                int y = num2.at(j) - '0';
                ansArr[i + j + 1] += x * y;
            }
        }
        for (int i = m + n - 1; i > 0; i--)
        {
            ansArr[i - 1] += ansArr[i] / 10;
            ansArr[i] %= 10;
        }
        int index = ansArr[0] == 0 ? 1 : 0;
        string ans;
        while (index < m + n)
        {
            ans.push_back(ansArr[index]);
            index++;
        }
        for (auto &c : ans)
        {
            c += '0';
        }
        return ans;
    }
};
// 把每一位与另一个字符串相乘的过程分开（即每一位与另一个字符串的每一位相乘），得到的数存int数组里（数字大小为string.size*n(n<=81)，所以不能在string里直接相加） 最后算进位（算了string.size次，我写的string1.size*string2.size次）
class Solution
{
public:
    using CP = complex<double>;

    static constexpr int MAX_N = 256 + 5;

    double PI;
    int n, aSz, bSz;
    CP a[MAX_N], b[MAX_N], omg[MAX_N], inv[MAX_N];

    void init()
    {
        PI = acos(-1);
        for (int i = 0; i < n; ++i)
        {
            omg[i] = CP(cos(2 * PI * i / n), sin(2 * PI * i / n));
            inv[i] = conj(omg[i]);
        }
    }

    void fft(CP *a, CP *omg)
    {
        int lim = 0;
        while ((1 << lim) < n)
            ++lim;
        for (int i = 0; i < n; ++i)
        {
            int t = 0;
            for (int j = 0; j < lim; ++j)
            {
                if ((i >> j) & 1)
                    t |= (1 << (lim - j - 1));
            }
            if (i < t)
                swap(a[i], a[t]);
        }
        for (int l = 2; l <= n; l <<= 1)
        {
            int m = l / 2;
            for (CP *p = a; p != a + n; p += l)
            {
                for (int i = 0; i < m; ++i)
                {
                    CP t = omg[n / l * i] * p[i + m];
                    p[i + m] = p[i] - t;
                    p[i] += t;
                }
            }
        }
    }

    string run()
    {
        n = 1;
        while (n < aSz + bSz)
            n <<= 1;
        init();
        fft(a, omg);
        fft(b, omg);
        for (int i = 0; i < n; ++i)
            a[i] *= b[i];
        fft(a, inv);
        int len = aSz + bSz - 1;
        vector<int> ans;
        for (int i = 0; i < len; ++i)
        {
            ans.push_back(int(round(a[i].real() / n)));
        }
        // 处理进位
        int carry = 0;
        for (int i = ans.size() - 1; i >= 0; --i)
        {
            ans[i] += carry;
            carry = ans[i] / 10;
            ans[i] %= 10;
        }
        string ret;
        if (carry)
        {
            ret += to_string(carry);
        }
        for (int i = 0; i < ans.size(); ++i)
        {
            ret.push_back(ans[i] + '0');
        }
        // 处理前导零
        int zeroPtr = 0;
        while (zeroPtr < ret.size() - 1 && ret[zeroPtr] == '0')
            ++zeroPtr;
        return ret.substr(zeroPtr, INT_MAX);
    }

    string multiply(string num1, string num2)
    {
        aSz = num1.size();
        bSz = num2.size();
        for (int i = 0; i < aSz; ++i)
            a[i].real(num1[i] - '0');
        for (int i = 0; i < bSz; ++i)
            b[i].real(num2[i] - '0');
        return run();
    }
};
// 快速傅里叶变换（数学 没看）