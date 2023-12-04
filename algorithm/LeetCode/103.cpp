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
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        if (root == nullptr)
            return {};
        vector<vector<int>> ans;
        // ans.emplace_back(vector<int>(1, root->val));
        stack<TreeNode *> s;
        s.push(root);
        while (1)
        {
            vector<int> tmp;
            {
                stack<TreeNode *> next;
                int num = s.size();
                for (int i = 0; i < num; i++)
                {
                    TreeNode *t = s.top();
                    s.pop();
                    if (t == nullptr)
                        continue;
                    tmp.emplace_back(t->val);
                    next.push(t->left);
                    next.push(t->right);
                }
                if (tmp.size())
                    ans.emplace_back(tmp);
                else
                    break;
                tmp.clear();
                s = next;
            }
            {
                int num = s.size();
                stack<TreeNode *> next;
                for (int i = 0; i < num; i++)
                {
                    TreeNode *t = s.top();
                    s.pop();
                    if (t == nullptr)
                        continue;
                    tmp.emplace_back(t->val);
                    next.push(t->right);
                    next.push(t->left);
                }
                if (tmp.size())
                    ans.emplace_back(tmp);
                else
                    break;
                s = next;
            }
        }
        return ans;
    }
};
// 我使用栈来达到锯齿状的逆向输出的

class Solution
{
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int>> ans;
        if (!root)
        {
            return ans;
        }

        queue<TreeNode *> nodeQueue;
        nodeQueue.push(root);
        bool isOrderLeft = true;

        while (!nodeQueue.empty())
        {
            deque<int> levelList;
            int size = nodeQueue.size();
            for (int i = 0; i < size; ++i)
            {
                auto node = nodeQueue.front();
                nodeQueue.pop();
                if (isOrderLeft)
                {
                    levelList.push_back(node->val);
                }
                else
                {
                    levelList.push_front(node->val);
                }
                if (node->left)
                {
                    nodeQueue.push(node->left);
                }
                if (node->right)
                {
                    nodeQueue.push(node->right);
                }
            }
            ans.emplace_back(vector<int>{levelList.begin(), levelList.end()});
            isOrderLeft = !isOrderLeft;
        }

        return ans;
    }
};
// 官方答案 只是将层序遍历得到的结果反转，功能上list可以代替，但deque也是数组，用迭代器范围构造vector时应该消耗更少吧