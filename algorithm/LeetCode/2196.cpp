class Solution {
public:
    string path, paths, pathd;
    void dfs(TreeNode* root, int s, int d) {
        if(root->val == s) paths = path;
        if(root->val == d) pathd = path;
        if(root->right) path += 'R', dfs(root->right, s, d), path.pop_back();
        if(root->left) path += 'L', dfs(root->left, s, d), path.pop_back();
    }
    string getDirections(TreeNode* root, int s, int d) {
        dfs(root, s, d);
        int i = 0, j = 0;
        while(paths[i] == pathd[j]) i++, j++;
        return string(paths.size() - i, 'U') + pathd.substr(j);
    }
};

//不懂为什么官方答案要用哈希表维护父节点，既然要遍历一遍，为什么不直接dfs返回追加向左还是向右，一直找到两个点。