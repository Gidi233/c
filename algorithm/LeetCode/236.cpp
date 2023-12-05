#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    unordered_map<int, TreeNode *> fa;
    unordered_map<int, bool> vis;
    void dfs(TreeNode *root)
    {
        if (root->left != nullptr)
        {
            fa[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right != nullptr)
        {
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        fa[root->val] = nullptr;
        dfs(root);
        while (p != nullptr)
        {
            vis[p->val] = true;
            p = fa[p->val];
        }
        while (q != nullptr)
        {
            if (vis[q->val])
                return q;
            q = fa[q->val];
        }
        return nullptr;
    }
};
// 哈希表   存每个点的父节点，和是否经过
// 我本来想用vector以层序遍历存节点，这样(index-1)/2就得到了父节点，但这样只能用于完全二叉树（要填充很多空指针，难以构造（或在遍历时传入pair<Treenode*,index>应该也可以））

class Solution
{
public:
    TreeNode *ans;
    bool dfs(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr)
            return false;
        bool lson = dfs(root->left, p, q);
        bool rson = dfs(root->right, p, q);
        if ((lson && rson) || ((root == p || root == q) && (lson || rson)))
        {
            ans = root;
        }
        return lson || rson || (root == p || root == q);
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        dfs(root, p, q);
        return ans;
    }
};
// dfs 因为是深度遍历从底部开始更新，按以下条件找到的就是最近公共祖先
// （flson && frson)||((x = p||x = q) && (flson||frson))
