// G(0)=1,G(1)=1
// 给定序列 1⋯n，我们选择数字 i 作为根，则根为 i 的所有二叉搜索树的集合是左子树集合和右子树集合的笛卡尔积(即左右乘积)
// 因为左右都是连续有序的，G(n) 和序列的内容无关，只和序列的长度有关！！
class Solution
{
public:
    int numTrees(int n)
    {
        vector<int> G(n + 1, 0);
        G[0] = 1;
        G[1] = 1;

        for (int i = 2; i <= n; ++i)
        {
            for (int j = 1; j <= i; ++j)
            {
                G[i] += G[j - 1] * G[i - j];
            }
        }
        return G[n];
    }
};

// 卡塔兰数
class Solution
{
public:
    int numTrees(int n)
    {
        long long C = 1;
        for (int i = 0; i < n; ++i)
        {
            C = C * 2 * (2 * i + 1) / (i + 2);
        }
        return (int)C;
    }
};
