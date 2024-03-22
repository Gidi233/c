#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  int widthOfBinaryTree(TreeNode* root) {
    list<pair<TreeNode*, unsigned int >> queue = {{root, 0}};
    unsigned int  size, ans = 0;
    while (size = queue.size()) {
      ans = max(ans, (queue.back().second - queue.front().second + 1));
      for (unsigned int  i = 0; i < size; i++) {
        auto node = queue.front();
        queue.pop_front();
        if (node.first->left != nullptr)
          queue.push_back({node.first->left, node.second * 2 + 1});
        if (node.first->right != nullptr)
          queue.push_back({node.first->right, node.second * 2 + 2});
      }
    }
    return ans;
  }
};
// 记录完全二叉树形式的下标，每一层算一次最大值
// 关键是这里借助无符号整型在溢出的时候自动根据32位，或者64位取模，取模后同一层的index会出现前大后小的情况，但因为是无符号整型，小减大后结果仍然正确
// signed溢出是ub,而unsigned不是

using ULL = unsigned long long;

class Solution {
 public:
  int widthOfBinaryTree(TreeNode* root) {
    unordered_map<int, ULL> levelMin;
    function<ULL(TreeNode*, int, ULL)> dfs = [&](TreeNode* node, int depth,
                                                 ULL index) -> ULL {
      if (node == nullptr) {
        return 0LL;
      }
      if (!levelMin.count(depth)) {
        levelMin[depth] =
            index;  // 每一层最先访问到的节点会是最左边的节点，即每一层编号的最小值
      }
      return max({index - levelMin[depth] + 1LL,
                  dfs(node->left, depth + 1, index * 2),
                  dfs(node->right, depth + 1, index * 2 + 1)});
    };
    return dfs(root, 1, 1LL);
  }
};
// 递归，记录每一层最左边的节点（也就是这一层第一次遇到的），然后计算当前节点和最左边节点的差值加1
