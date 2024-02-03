class Solution
{
public:
    int compareVersion(string version1, string version2)
    {
        int v1 = 0, v2 = 0, l1 = version1.length() + 1, l2 = version2.length() + 1;
        size_t i1 = 0, i2 = 0;
        while (1)
        {
            if (i1 == l1 && i2 == l2)
                return 0;
            if (i1 == l1)
                v1 = 0;
            else
            {
                size_t t;
                v1 = stoi(version1.substr(i1), &t);
                i1 += t + 1;
            }
            if (i2 == l2)
                v2 = 0;
            else
            {
                size_t t;
                v2 = stoi(version2.substr(i2), &t);
                i2 += t + 1;
            }
            if (v1 == v2)
                continue;
            if (v1 > v2)
                return 1;
            else
                return -1;
        }
    }
};
// substr复制了 就跟split差不多 比split复制的还多

class Solution
{
public:
    int compareVersion(string version1, string version2)
    {
        int n = version1.length(), m = version2.length();
        int i = 0, j = 0;
        while (i < n || j < m)
        {
            int x = 0;
            for (; i < n && version1[i] != '.'; ++i)
            {
                x = x * 10 - '0' + version1[i];
            }
            ++i; // 跳过点号
            int y = 0;
            for (; j < m && version2[j] != '.'; ++j)
            {
                y = y * 10 - '0' + version2[j];
            }
            ++j; // 跳过点号
            if (x != y)
            {
                return x > y ? 1 : -1;
            }
        }
        return 0;
    }
};
