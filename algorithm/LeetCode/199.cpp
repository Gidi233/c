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
    vector<int> rightSideView(TreeNode *root)
    {
        if(!root)
            return {};
        vector<int> ans;
        queue<TreeNode *> s;
        s.push(root);
        int num;
        while (num = s.size())
        {
            for (int i = 0; i < num; i++)
            {
                TreeNode *node = s.front();
                if (i == num - 1)
                    ans.push_back(node->val);
                s.pop();
                if (node->left)
                    s.push(node->left);
                if (node->right)
                    s.push(node->right);
            }
        }
        return ans;
    }
};
// 获取每次层序遍历的最后一个
class Solution
{
    vector<int> ans;

    void dfs(TreeNode *node, int depth)
    {
        if (node == nullptr)
            return;
        if (depth == ans.size())
            ans.push_back(node->val);
        dfs(node->right, depth + 1);
        dfs(node->left, depth + 1);
    }

public:
    vector<int> rightSideView(TreeNode *root)
    {
        dfs(root, 0);
        return ans;
    }
};
// dfs