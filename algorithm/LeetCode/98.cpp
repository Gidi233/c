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
    bool flag = 1;
    int left(TreeNode *root)
    {
        if (!flag)
            return 0;
        int l = root->left ? left(root->left) : INT_MIN, r = root->right ? right(root->right) : INT_MAX;
        if (!flag)
            return 0;
        if (l < root->val && root->val < r)
            return r;
        else
            flag = 0;
    }
    int right(TreeNode *root)
    {
        if (!flag)
            return 0;
        int l = root->left ? left(root->left) : INT_MIN, r = root->right ? right(root->right) : INT_MAX;
        if (!flag)
            return 0;
        if (l < root->val && root->val < r)
            return l;
        else
            return 0;
    }
    bool isValidBST(TreeNode *root)
    {
        int l = root->left ? left(root->left) : INT_MIN, r = root->right ? right(root->right) : INT_MAX;
        if (l < root->val && root->val < r)
            return flag;
        else
            return 0;
    }
};
// 从下往上，返回大小限制，还要改逻辑，不能直接给极值
// 后序
class Solution
{
public:
    bool helper(TreeNode *root, long long lower, long long upper)
    {
        if (root == nullptr)
        {
            return true;
        }
        if (root->val <= lower || root->val >= upper)
        {
            return false;
        }
        return helper(root->left, lower, root->val) && helper(root->right, root->val, upper);
    }
    bool isValidBST(TreeNode *root)
    {
        return helper(root, LONG_MIN, LONG_MAX);
    }
};
// 从上往下递归，传入大小限制
// 前序
class Solution
{
    long pre = LONG_MIN;

public:
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        if (!isValidBST(root->left) || root->val <= pre)
            return false;
        pre = root->val;
        return isValidBST(root->right);
    }
};
// 中序 二叉搜索树 升序

// 感觉层序也可以，每层递增