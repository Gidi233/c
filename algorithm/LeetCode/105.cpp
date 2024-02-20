
class Solution
{
private:
    unordered_map<int, int> index;

public:
    bool left(int num, int compare)
    {
        if (index[num] < index[compare])
            return 1;
        else
            return 0;
    }

    // bool left(int num, vector<int> &inorder, int compare)
    // {
    //     for (int i = 0; i < inorder.size(); i++)
    //     {
    //         if (inorder[i] == num)
    //             return true;
    //         if (inorder[i] == compare)
    //             return false;
    //     }
    //     return 0; // 不会到这
    // }这里改成用哈希映射存，就不用每次都遍历一遍了。
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int n = preorder.size();
        // 构造哈希映射，帮助我们快速定位根节点
        for (int i = 0; i < n; ++i)
        {
            index[inorder[i]] = i;
        }

        TreeNode *head = new TreeNode(preorder[0]);
        for (int i = 1; i < preorder.size(); i++)
        {
            TreeNode *cun = head;
            int num = preorder[i];
            while (1)
            {
                if (left(num, cun->val))
                {
                    if (cun->left != nullptr)
                        cun = cun->left;
                    else
                    {
                        cun->left = new TreeNode(num);
                        break;
                    }
                }
                else
                {
                    if (cun->right != nullptr)
                        cun = cun->right;
                    else
                    {
                        cun->right = new TreeNode(num);
                        break;
                    }
                }
            }
        }
        return head;
    }
};
// 我写的迭代   每次都把树遍历一遍才能找到插入点

class Solution
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (!preorder.size())
        {
            return nullptr;
        }
        TreeNode *root = new TreeNode(preorder[0]);
        stack<TreeNode *> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i)
        {
            int preorderVal = preorder[i];
            TreeNode *node = stk.top();
            if (node->val != inorder[inorderIndex])
            {
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            }
            else
            {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex])
                {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};
// 迭代 没太看懂 用一个栈来维护「当前节点的所有还没有考虑过右儿子的祖先节点」，栈顶就是当前节点，就不用每次都把树遍历一遍了。
class Solution
{
private:
    unordered_map<int, int> index;

public:
    TreeNode *myBuildTree(const vector<int> &preorder, const vector<int> &inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right)
    {
        if (preorder_left > preorder_right)
        {
            return nullptr;
        }

        // 前序遍历中的第一个节点就是根节点
        int preorder_root = preorder_left;
        // 在中序遍历中定位根节点
        int inorder_root = index[preorder[preorder_root]];

        // 先把根节点建立出来
        TreeNode *root = new TreeNode(preorder[preorder_root]);
        // 得到左子树中的节点数目
        int size_left_subtree = inorder_root - inorder_left;
        // 递归地构造左子树，并连接到根节点
        // 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
        root->left = myBuildTree(preorder, inorder, preorder_left + 1, preorder_left + size_left_subtree, inorder_left, inorder_root - 1);
        // 递归地构造右子树，并连接到根节点
        // 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
        root->right = myBuildTree(preorder, inorder, preorder_left + size_left_subtree + 1, preorder_right, inorder_root + 1, inorder_right);
        return root;
    }

    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int n = preorder.size();
        // 构造哈希映射，帮助我们快速定位根节点
        for (int i = 0; i < n; ++i)
        {
            index[inorder[i]] = i;
        }
        return myBuildTree(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};
// 递归
// 对于任意一颗树而言，前序遍历的形式总是
// [ 根节点, [左子树的前序遍历结果], [右子树的前序遍历结果] ]
// 即根节点总是前序遍历中的第一个节点。而中序遍历的形式总是
// [ [左子树的中序遍历结果], 根节点, [右子树的中序遍历结果] ]

