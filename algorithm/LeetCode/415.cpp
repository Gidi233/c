class Solution
{
public:
    void add(string &num1, string &num2)
    {
        int size1 = num1.size() - 1, size2 = num2.size() - 1;

        while (size2 > 0)
        {
            int tmp = num1[size1] - '0' + num2[size2] - '0';
            num1[size1--] = tmp % 10 + '0';
            if (tmp >= 10)
                num1[size1]++;
            size2--;
        } // 处理完短的
        num1[size1] += num2[0] - '0';
        while (size1 > 0) // 处理长的进位
        {
            if (num1[size1] > '9')
            {
                num1[size1--] = (num1[size1] - '9' - 1) + '0';
                num1[size1]++;
            }
            else
                return;
        }
        if (num1[size1] > '9')
        {
            num1[size1] = (num1[size1] - '9' - 1) + '0';
            num1.insert(0, 1, '1');
        }
    }
    string addStrings(string num1, string num2)
    {
        int size1 = num1.size() - 1, size2 = num2.size() - 1;
        if (size1 < size2)
            swap(num1, num2);
        add(num1, num2);
        return num1;
    }
};
// string的函数做到的

// 感觉不如下面官方的直观
class Solution
{
public:
    string addStrings(string num1, string num2)
    {
        int i = num1.length() - 1, j = num2.length() - 1, add = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || add != 0)
        {
            int x = i >= 0 ? num1[i] - '0' : 0;
            int y = j >= 0 ? num2[j] - '0' : 0;
            int result = x + y + add;
            ans.push_back('0' + result % 10);
            add = result / 10;
            i -= 1;
            j -= 1;
        }
        // 计算完以后的答案需要翻转过来
        reverse(ans.begin(), ans.end());
        return ans;
    }
};