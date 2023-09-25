class Solution
{
public:
    vector<string> vec = {};
    void func(int x, int y, string str)
    {
        if (!x && !y)
            vec.emplace_back(str);
        if (x)
            func(x - 1, y + 1, str + '(');
        if (y)
            func(x, y - 1, str + ')');
    }
    vector<string> generateParenthesis(int n)
    {
        func(n, 0, "");
        return vec;
    }
};
// 参数传递待添加'(',待添加')'，和已生成的string.

class Solution
{
    void backtrack(vector<string> &ans, string &cur, int open, int close, int n)
    {
        if (cur.size() == n * 2)
        {
            ans.push_back(cur);
            return;
        }
        if (open < n)
        {
            cur.push_back('(');
            backtrack(ans, cur, open + 1, close, n);
            cur.pop_back();
        }
        if (close < open)
        {
            cur.push_back(')');
            backtrack(ans, cur, open, close + 1, n);
            cur.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> result;
        string current;
        backtrack(result, current, 0, 0, n);
        return result;
    }
};

// 官方答案，跟上面的想法一样

class Solution
{
    shared_ptr<vector<string>> cache[100] = {nullptr};

public:
    shared_ptr<vector<string>> generate(int n)
    {
        if (cache[n] != nullptr)
            return cache[n];
        if (n == 0)
        {
            cache[0] = shared_ptr<vector<string>>(new vector<string>{""});
        }
        else
        {
            auto result = shared_ptr<vector<string>>(new vector<string>);
            for (int i = 0; i != n; ++i)
            {
                auto lefts = generate(i);
                auto rights = generate(n - i - 1);
                for (const string &left : *lefts)
                    for (const string &right : *rights)
                        result->push_back("(" + left + ")" + right);
            }
            cache[n] = result;
        }
        return cache[n];
    }
    vector<string> generateParenthesis(int n)
    {
        return *generate(n);
    }
};

// 用一个结构记录之前算出的n的vector<string>，分别插入(a)b的a、b中（为0-至n-1的vector<string>）
