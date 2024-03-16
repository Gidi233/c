class Solution {
 public:
  bool dfs(TreeNode* root, int num, int targetSum) {
    if (root == nullptr) return false;
    int newnum = num + root->val;
    if (root->left != nullptr && root->right != nullptr) {
      if (newnum == targetSum)
        return true;
      else
        return false;
    } else
      return dfs(root->left, newnum, targetSum) ||
             dfs(root->right, newnum, targetSum);
  }

  bool hasPathSum(TreeNode* root, int targetSum) {
    return dfs(root, 0, targetSum);
  }
};
// 十分钟解决战斗 树的遍历

class Solution {
 public:
  bool hasPathSum(TreeNode* root, int sum) {
    if (root == nullptr) {
      return false;
    }
    if (root->left == nullptr && root->right == nullptr) {
      return sum == root->val;
    }
    return hasPathSum(root->left, sum - root->val) ||
           hasPathSum(root->right, sum - root->val);
  }
};

// 官方题解 两个参数