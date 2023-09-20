/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    queue<pair<TreeNode *, int>> que;
    int minDepth(TreeNode *root)
    {
        if (!root)
            return 0;
        TreeNode *cun = root;
        int num = 1;
        while (cun->left || cun->right)
        {
            if (cun->left)
            {
                que.emplace(cun->left, num + 1);
            }
            if (cun->right)
            {
                que.emplace(cun->right, num + 1);
            }
            auto cur = que.front();
            que.pop();
            cun = cur.first;
            num = cur.second;
        }
        return num;
    }
};
// 我写的广搜
class Solution
{
public:
    int minDepth(TreeNode *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        queue<pair<TreeNode *, int>> que;
        que.emplace(root, 1);
        while (!que.empty())
        {
            TreeNode *node = que.front().first;
            int depth = que.front().second;
            que.pop();
            if (node->left == nullptr && node->right == nullptr)
            {
                return depth;
            }
            if (node->left != nullptr)
            {
                que.emplace(node->left, depth + 1);
            }
            if (node->right != nullptr)
            {
                que.emplace(node->right, depth + 1);
            }
        }

        return 0;
    }
};
// 官方广搜
class Solution
{
public:
    int minDepth(TreeNode *root)
    {
        if (root == nullptr)
        {
            return 0;
        }

        if (root->left == nullptr && root->right == nullptr)
        {
            return 1;
        }

        int min_depth = INT_MAX;
        if (root->left != nullptr)
        {
            min_depth = min(minDepth(root->left), min_depth);
        }
        if (root->right != nullptr)
        {
            min_depth = min(minDepth(root->right), min_depth);
        }

        return min_depth + 1;
    }
};
// 深搜