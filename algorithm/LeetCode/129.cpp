
class Solution
{
public:
    int dfs(TreeNode *node, int num)
    {
        // if (root == nullptr)代替后面那一堆三目表达式
        // {
            // return 0;
        // }
        if (!node->left && !node->right)
            return num * 10 + node->val;
        return (node->left ? dfs(node->left, num * 10 + node->val) : 0) + (node->right ? dfs(node->right, num * 10 + node->val) : 0);
    }
    int sumNumbers(TreeNode *root)
    {
        return root ? dfs(root, 0) : 0;
    }
};