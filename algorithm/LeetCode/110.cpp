
class Solution
{
public:
    bool flag = 1;
    int dfs(TreeNode *node, int depth)
    {
        if (node == nullptr)
            return depth - 1;

        int l = dfs(node->left, depth + 1);
        if (!flag)
            return -1;
        int r = dfs(node->right, depth + 1);
        if (!flag)
            return -1;
        if (abs(l - r) < 2)
            return max(l, r);
        else
            flag = 0;
        return -1;
    }

    bool isBalanced(TreeNode *root)
    {
        dfs(root, 0);
        return flag;
    }
};
// 脑袋一抽 就写成这样了 思想一样 看后面标答吧
class Solution
{
public:
    int height(TreeNode *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1)
        {
            return -1;
        }
        else
        {
            return max(leftHeight, rightHeight) + 1;
        }
    }

    bool isBalanced(TreeNode *root)
    {
        return height(root) >= 0;
    }
};
