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