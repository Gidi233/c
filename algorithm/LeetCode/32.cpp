class Solution
{
public:
    int search(string s, int &index)
    {
        stack<char> stack;
        int ans = 0;
        for (; index < s.size(); index++)
        {
            if (s[index] == '(')
            {
                stack.push(s[index]);
            }
            if (s[index] == ')')
            {
                if (stack.empty())
                    return ans * 2;
                ++ans;
                stack.pop();
            }
        }
        return ans * 2;
    }
    int longestValidParentheses(string s)
    {
        int ans = 0;
        for (int i = 0; i < s.size(); i++)
        {
            ans = max(ans, search(s, i));
        }
        return ans;
    }
};
// 没用把有用的数据放入栈中，用匹配了几个')'来数长度，"()(()"会错误

class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int maxans = 0, n = s.length();
        vector<int> dp(n, 0);
        for (int i = 1; i < n; i++)
        {
            if (s[i] == ')')
            {
                if (s[i - 1] == '(')
                {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                }
                else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(')
                {
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
                maxans = max(maxans, dp[i]);
            }
        }
        return maxans;
    }
};

// 状态转移方程：dp[i]=dp[i−1]+dp[i−dp[i−1]−2]+2

class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int maxans = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                stk.push(i);
            }
            else
            {
                stk.pop();
                if (stk.empty())
                {
                    stk.push(i);
                }
                else
                {
                    maxans = max(maxans, i - stk.top());
                    // cout<<maxans<<endl;
                }
            }
        }
        return maxans;
    }
};
// 通过把下标放入栈中来计算长度
// 对于遇到的每个 ‘(’，我们将它的下标放入栈中
// 对于遇到的每个 ‘)’，我们先弹出栈顶元素来匹配了当前右括号：
// 如果栈为空，说明当前的右括号为没有被匹配的左括号，我们将其下标放入栈中来更新我们之前提到的「最后一个没有被匹配的右括号的下标」（连续括号的新起始点、分隔符）
// 如果栈不为空，当前右括号的下标减去栈顶元素即为「以该右括号为结尾的最长有效括号的长度」

class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int left = 0, right = 0, maxlength = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                left++;
            }
            else
            {
                right++;
            }
            if (left == right)
            {
                maxlength = max(maxlength, 2 * right);
            }
            else if (right > left)
            {
                left = right = 0;
            }
        }
        left = right = 0;
        for (int i = (int)s.length() - 1; i >= 0; i--)
        {
            if (s[i] == '(')
            {
                left++;
            }
            else
            {
                right++;
            }
            if (left == right)
            {
                maxlength = max(maxlength, 2 * left);
            }
            else if (left > right)
            {
                left = right = 0;
            }
        }
        return maxlength;
    }
};
// 从左到右遍历字符串，对于遇到的每个 ‘(’，我们增加 left 计数器，对于遇到的每个 ‘)’ ，我们增加 right 计数器。每当 left 计数器与 right 计数器相等时，我们计算当前有效字符串的长度，并且记录目前为止找到的最长子字符串。当 right 计数器比 left 计数器大时，我们将 left 和 right 计数器同时变回 0。
// 会漏掉一种情况，就是遍历的时候左括号的数量始终大于右括号的数量，即 (()。解决的方法也很简单，我们只需要从右往左遍历用类似的方法计算即可，只是这个时候判断条件反了过来
