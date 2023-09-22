class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> stack;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '{' || s[i] == '(' || s[i] == '[')
            {
                stack.push(s[i]);
            }
            if (s[i] == '}' || s[i] == ')' || s[i] == ']')
            {
                if (stack.empty())
                    return 0;
                char a = stack.top();
                stack.pop();
                if (a == '(' && s[i] == ')')
                    continue;
                if (a == '{' && s[i] == '}')
                    continue;
                if (a == '[' && s[i] == ']')
                    continue;
                return 0;
            }
        }
        if (!stack.empty())
            return 0;
        return 1;
    }
};

class Solution
{
public:
    bool isValid(string s)
    {
        int n = s.size();
        if (n % 2 == 1)
        {
            return false;
        }

        unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}};
        stack<char> stk;
        for (char ch : s)
        {
            if (pairs.count(ch))
            {
                if (stk.empty() || stk.top() != pairs[ch])
                {
                    return false;
                }
                stk.pop();
            }
            else
            {
                stk.push(ch);
            }
        }
        return stk.empty();
    }
};

// 官方答案 用了一个哈希表来存储关系。不然就是一堆if