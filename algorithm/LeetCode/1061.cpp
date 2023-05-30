class Solution {
public:
    struct DSU {
        vector<int> F;
        int find(int x) {
            if (F[x] != x) F[x] = find(F[x]);
            return F[x];
        }
        void unite(int x, int y) {
            int f1 = find(x);
            int f2 = find(y);
            F[f1] = F[f2] = min(f1, f2);
        }
        DSU() {
            F = vector<int>(26, 0);
            for (int i = 0; i < 26; ++i) F[i] = i;
        };
    };
    
    string smallestEquivalentString(string A, string B, string S) {
        DSU dsu;
        for (int i = 0; i < A.size(); ++i) {
            dsu.unite(A[i] - 'a', B[i] - 'a');
        }
        string res;
        for (auto x : S) {
            res += dsu.find(x - 'a') + 'a';
        }
        return res;
    }
};
//并查集，将两个数据以给定顺序归为一类（大/小），先建表，再将给定数据归为一类，题目要最小字符串，就把大的指向小的，若表中数据不指向自身，就递归查找（找到归为一类的最小值）。