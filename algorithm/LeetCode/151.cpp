#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string reverseWords(string s)
    {
        string ans;
        int index = s.find_last_not_of(' ');
        bool first = false;
        while (index>=0)
        {
            while (index >= 0 && s[index] == ' ')
                index--;
            int tail = index;
            while (index>=0&&s[index] != ' ')
                index--;
            if(index==-1&&tail==index)
                return ans;
            if (!first)
                first = 1;
            else
                ans += ' ';
            ans += s.substr(index+1, tail-index);
        }
        return ans;
    }
};
int main()
{
    Solution solution;
    cout << solution.reverseWords("  hello world  ") << endl;
}