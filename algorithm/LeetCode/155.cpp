class MinStack
{
private:
    stack<long> S;
    int min;

public:
    MinStack()
    {
    }

    void push(long val)
    {
        if (S.empty())
            min = val;
        long t = val - min;
        S.push(t);
        if (t < 0)
            min = val;
    }

    void pop()
    {
        long t = S.top();
        if (t < 0)
            min -= t;
        S.pop();
    }

    int top()
    {
        long t = S.top();
        if (t < 0)
            return min;
        else
            return min + t;
    }

    int getMin()
    {
        return min;
    }
};
// 在栈里存差值，就不用用多余空间存之前的最小值 
// 因为是差值，用int会溢出