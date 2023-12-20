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
    vector<int> ans;
    void dfs(TreeNode *root)
    {
        if(root == nullptr)return;
        dfs(root->left);
        ans.push_back(root->val);
        dfs(root->right);
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        ans.clear();
        dfs(root);
        return ans;
    }
};

class Solution
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> res;
        stack<TreeNode *> stk;
        while (root != nullptr || !stk.empty())
        {
            while (root != nullptr)
            {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
};
// 迭代

class Solution
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> res;
        TreeNode *predecessor = nullptr;

        while (root != nullptr)
        {
            if (root->left != nullptr)
            {
                // predecessor 节点就是当前 root 节点向左走一步，然后一直向右走至无法走为止
                predecessor = root->left;
                while (predecessor->right != nullptr && predecessor->right != root)
                {
                    predecessor = predecessor->right;
                }

                // 让 predecessor 的右指针指向 root，继续遍历左子树
                if (predecessor->right == nullptr)
                {
                    predecessor->right = root;
                    root = root->left;
                }
                // 说明左子树已经访问完了，我们需要断开链接
                else
                {
                    res.push_back(root->val);
                    predecessor->right = nullptr;
                    root = root->right;
                }
            }
            // 如果没有左孩子，则直接访问右孩子
            else
            {
                res.push_back(root->val);
                root = root->right;
            }
        }
        return res;
    }
};
// 其实整个过程我们就多做一步：假设当前遍历到的节点为 x，将 x 的左子树中最右边的节点的右孩子指向 x，这样在左子树遍历完成后我们通过这个指向走回了 x，且能通过这个指向知晓我们已经遍历完成了左子树，而不用再通过栈来维护，省去了栈的空间复杂度。
// 像在构造线索二叉树，提前得到后继节点