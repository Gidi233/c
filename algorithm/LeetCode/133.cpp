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
  vector<vector<int>> ans;
  void dfs(TreeNode* root, vector<int>& tmp, int cun, int sum) {
    if (!root) return;
    int num = cun + root->val;
    if (num == sum) {
      if (root->left == nullptr && root->right == nullptr) {
        tmp.push_back(root->val);
        ans.push_back(tmp);
        tmp.pop_back();
      }
      else return;
    }
    tmp.push_back(root->val);
    dfs(root->left, tmp, num, sum);
    dfs(root->right, tmp, num, sum);
    tmp.pop_back();
  }
  vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<int> tmp;
    dfs(root, tmp, 0, targetSum);
    return ans;
  }
};
int main() { Solution solution;
  TreeNode* a = new TreeNode(-2, 0, new TreeNode(-3));
  solution.pathSum(a,-5);
}