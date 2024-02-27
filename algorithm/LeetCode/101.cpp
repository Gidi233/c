
class Solution
{
public:
    stack<TreeNode *> l, r; // queue也行
    bool isSymmetric(TreeNode *root)
    {
        if (root->left == nullptr && root->right == nullptr)
            return 1;
        if (root->left != nullptr && root->right != nullptr ? root->left->val != root->right->val : root->left != root->right)
            return 0;
        l.push(root->left);
        r.push(root->right);
        while (l.size()) // 随便哪个都行 两个是相等的
        {
            TreeNode *left = l.top(), *right = r.top();
            l.pop();
            r.pop();
            if ((left->left != nullptr && right->right != nullptr) ? left->left->val == right->right->val : right->right == left->left) //(!u || !v) || (u->val != v->val)这逻辑我推不出来？？？
            {
                if (right->right != nullptr)
                    r.push(right->right);
                if (left->left != nullptr)
                    l.push(left->left);
            }
            else
                return 0;
            if ((left->right != nullptr && right->left != nullptr) ? left->right->val == right->left->val : right->left == left->right)
            {
                if (right->left != nullptr)
                    r.push(right->left);
                if (left->right != nullptr)
                    l.push(left->right);
            }
            else
                return 0;
        }
        return 1;
    }
};
// ？：真是狗屎的可读性
// 用两个栈或队列分别存根节点两边的对称节点
class Solution
{
public:
    bool check(TreeNode *u, TreeNode *v)
    {
        queue<TreeNode *> q;
        q.push(u);
        q.push(v);
        while (!q.empty())
        {
            u = q.front();
            q.pop();
            v = q.front();
            q.pop();
            if (!u && !v)
                continue;
            if ((!u || !v) || (u->val != v->val))
                return false;

            q.push(u->left);
            q.push(v->right);

            q.push(u->right);
            q.push(v->left);
        }
        return true;
    }

    bool isSymmetric(TreeNode *root)
    {
        return check(root, root);
    }
};
// 官解 用一个队列 一次退两个 然后 简洁多了
class Solution
{
public:
    bool check(TreeNode *p, TreeNode *q)
    {
        if (!p && !q)
            return true;
        if (!p || !q)
            return false;
        return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
    }

    bool isSymmetric(TreeNode *root)
    {
        return check(root, root);
    }
};
// 递归