#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int ans;
    int dfs(TreeNode *node)
    {

        if (!node)
            return 0;
        int l = dfs(node->left), r = dfs(node->right);
        ans = max(l + r, ans);
        return max(l, r) + 1;
    }
    int diameterOfBinaryTree(TreeNode *root)
    {
        ans = 0;
        if (!root)
            return 0;
        dfs(root);
        return ans;
    }
};
int main()
{
    Solution solution;
}