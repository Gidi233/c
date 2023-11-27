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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        if (root == nullptr)
            return {};
        queue<TreeNode *> child;
        vector<vector<int>> ans;
        child.push(root);
        while (!child.empty())
        {
            queue<TreeNode *> tmp;
            vector<int> floor;
            while (!child.empty())
            {
                TreeNode *node=child.front();
                child.pop();
                floor.emplace_back(node->val);
                if(node->left!=nullptr)
                    tmp.push(node->left);
                if (node->right != nullptr)
                    tmp.push(node->right);
            }
            child = tmp;
            ans.emplace_back(floor);
        }
        return ans;
    }
};
// 广度优先搜索

class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (!root)
        {
            return ret;
        }

        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            int currentLevelSize = q.size();
            ret.push_back(vector<int>());
            for (int i = 1; i <= currentLevelSize; ++i)
            {
                auto node = q.front();
                q.pop();
                ret.back().push_back(node->val);
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }

        return ret;
    }
};
// 官方答案，每次都先拿到队列的长度（即循环次数），就不需要在定义一个tmp