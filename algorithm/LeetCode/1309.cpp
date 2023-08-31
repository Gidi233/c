class Solution
{
public:
    string freqAlphabets(string s)
    {
        char c[1005] = "";
        int rlen = 0;
        for (int i = 2; i < s.size(); i++)
        {
            if (s[i] == '#')
            {
                int num = stoi(s.substr(i - 2, 2)) - 1;
                c[rlen++] = 'a' + num;
                i = i + 2;
            }
            else
                c[rlen++] = s[i - 2] + 48;
        }
        for (int i = s.find_last_of('#') + 1; i < s.size(); i++) // 用来判断最后不是#的情况
            c[rlen++] = s[i] + 48;
        return string(c);
    }
};
// 如果从后往前判断的话就不用后面那个循环
//  最后reverse(ans.begin(), ans.end());就行