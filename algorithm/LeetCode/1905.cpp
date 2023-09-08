class Solution
{
private:
    static constexpr array<array<int, 2>, 4> dirs = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

public:
    int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2)
    {
        int m = grid1.size(), n = grid1[0].size();

        auto bfs = [&](int sx, int sy)
        {
            queue<pair<int, int>> q;
            q.emplace(sx, sy);
            grid2[sx][sy] = 0;
            // 判断岛屿包含的每一个格子是否都在 grid1 中出现了
            bool check = grid1[sx][sy];
            while (!q.empty())
            {
                auto [x, y] = q.front();
                q.pop();
                for (int d = 0; d < 4; ++d)
                {
                    int nx = x + dirs[d][0];
                    int ny = y + dirs[d][1];
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid2[nx][ny] == 1)
                    {
                        q.emplace(nx, ny);
                        grid2[nx][ny] = 0;
                        if (grid1[nx][ny] != 1)
                        {
                            check = false;
                        }
                    }
                }
            }
            return check;
        };

        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid2[i][j] == 1)
                {
                    ans += bfs(i, j);
                }
            }
        }
        return ans;
    }
};
// 广搜

class Solution
{
private:
    static constexpr array<array<int, 2>, 4> dirs = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

public:
    int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2)
    {
        int m = grid1.size(), n = grid1[0].size();
        bool check;
        std::function<bool(int, int)> dfs = [&](int sx, int sy) { // 要递归lambda的话，因为其匿名，要把它包装成对象,用lambda就不用传两个二维数组参数了
            grid2[sx][sy] = 0;
            // 判断岛屿包含的每一个格子是否都在 grid1 中出现了

            for (int d = 0; d < 4; ++d)
            {
                int nx = sx + dirs[d][0];
                int ny = sy + dirs[d][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid2[nx][ny] == 1)
                {
                    if (grid1[nx][ny] != 1)
                    {
                        check = false;
                    }
                    dfs(nx, ny);
                }
            }

            return check;
        };

        int ans = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid2[i][j] == 1)
                {
                    check = grid1[i][j]; // 只检查一次为1的情况，后面一旦有0，就置为0
                    ans += dfs(i, j);
                }
            }
        }
        return ans;
    }
};
// 深搜