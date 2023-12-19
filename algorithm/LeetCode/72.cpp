class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int n = word1.length();
        int m = word2.length();

        // 有一个字符串为空串
        if (n * m == 0)
            return n + m;

        // DP 数组
        vector<vector<int>> D(n + 1, vector<int>(m + 1));

        // 边界状态初始化
        for (int i = 0; i < n + 1; i++)
        {
            D[i][0] = i;
        }
        for (int j = 0; j < m + 1; j++)
        {
            D[0][j] = j;
        }

        // 计算所有 DP 值
        for (int i = 1; i < n + 1; i++)
        {
            for (int j = 1; j < m + 1; j++)
            {
                int left = D[i - 1][j] + 1;
                int down = D[i][j - 1] + 1;
                int left_down = D[i - 1][j - 1];
                if (word1[i - 1] != word2[j - 1])
                    left_down += 1;
                D[i][j] = min({left, down, left_down});
            }
        }
        return D[n][m];
    }
};
// 固定b，让a编辑成b，抽象为以下三个行为
// 在单词 A 中插入一个字符：如果我们知道 horse 到 ro 的编辑距离为 a，那么显然 horse 到 ros 的编辑距离不会超过 a + 1。这是因为我们可以在 a 次操作后将 horse 和 ro 变为相同的字符串，只需要额外的 1 次操作，在单词 A 的末尾添加字符 s，就能在 a + 1 次操作后将 horse 和 ro 变为相同的字符串；
// 在单词 A 中删除一个字符：如果我们知道 hors 到 ro 的编辑距离为 b，那么显然 horse 到 ros 的编辑距离不会超过 b + 1，原因同上；
// 修改单词 A 的一个字符：如果我们知道 hors 到 ro 的编辑距离为 c，那么显然 horse 到 ros 的编辑距离不会超过 c + 1，原因同上。
// 状态转移方程分两种情况：（word1的前i个转变为word2的前j个进行的操作数）
// 若 A 和 B 的最后一个字母相同：
// D[i][j]=1+min(D[i][j−1],D[i−1][j],D[i−1][j−1]−1)
// 若 A 和 B 的最后一个字母不同：
// D[i][j]=1+min(D[i][j−1],D[i−1][j],D[i−1][j−1])

class Solution
{
public:
    int minDistance(string s, string t)
    {
        int n = s.length(), m = t.length(), f[2][m + 1];
        for (int j = 0; j <= m; ++j)
            f[0][j] = j;
        for (int i = 0; i < n; ++i)
        {
            f[(i + 1) % 2][0] = i + 1;
            for (int j = 0; j < m; ++j)
                f[(i + 1) % 2][j + 1] = s[i] == t[j] ? f[i % 2][j] : min(min(f[i % 2][j + 1], f[(i + 1) % 2][j]), f[i % 2][j]) + 1;
        }
        return f[n % 2][m];
    }
};
// 灵神
//  空间优化：两个数组（滚动数组）
// 因为只会用到前一个所以，可以覆盖

class Solution
{
public:
    int minDistance(string s, string t)
    {
        int m = t.length(), f[m + 1];
        iota(f, f + m + 1, 0);
        for (char x : s)
        {
            int pre = f[0];
            ++f[0];
            for (int j = 0; j < m; ++j)
            {
                int tmp = f[j + 1];
                f[j + 1] = x == t[j] ? pre : min(min(f[j + 1], f[j]), pre) + 1;
                pre = tmp;
            }
        }
        return f[m];
    }
};
// 用一个数组的版本，用pre存储了f[i-1][j-1]