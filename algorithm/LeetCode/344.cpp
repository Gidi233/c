class Solution
{
public:
    void reverseString(vector<char> &s)
    {
        int len = s.size() - 1;
        for (int i = 0; i <= (len - 1) / 2; i++)
        {
            int temp = s[i];
            s[i] = s[len - i];
            s[len - i] = temp;
        }
    }
};

class Solution
{
public:
    void reverseString(vector<char> &s)
    {
        int n = s.size();
        for (int left = 0, right = n - 1; left < right; ++left, --right)
        {
            swap(s[left], s[right]);
        }
    }
};
// 感觉双指针更直观