class Solution
{
public:
    int mySqrt(int x)
    {
        unsigned long l = 0, r = x;
        while (l < r)
        {
            unsigned long mid = l + (r - l + 1) / 2;
            if (mid * mid > x)
                r = mid - 1;
            else
                l = mid;
        }
        return l;
    }
};
// 二分

class Solution
{
public:
    int mySqrt(int x)
    {
        if (x == 0)
        {
            return 0;
        }

        double C = x, x0 = x;
        while (true)
        {
            double xi = 0.5 * (x0 + C / x0);
            if (fabs(x0 - xi) < 1e-7)
            {
                break;
            }
            x0 = xi;
        }
        return int(x0);
    }
};
// 牛顿迭代法推公式