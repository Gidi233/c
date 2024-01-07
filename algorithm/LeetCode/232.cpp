#include <bits/stdc++.h>
using namespace std;

class MyQueue
{
public:
    MyQueue() = default;

    void push(int x)
    {
        first.push(x);
    }

    int pop()
    {
        stack<int> tmp;
        while (first.size())
        {
            tmp.push(first.top());
            first.pop();
        }
        int ans = tmp.top();
        tmp.pop();
        while (tmp.size())
        {
            first.push(tmp.top());
            tmp.pop();
        }
    }

    int peek()
    {
        stack<int> tmp;
        while (first.size())
        {
            tmp.push(first.top());
            first.pop();
        }
        int ans = tmp.top();
        while (tmp.size())
        {
            first.push(tmp.top());
            tmp.pop();
        }
    }

    bool empty()
    {
        return first.empty();
    }

private:
    stack<int> first;
};
//我这每次输出都要倒两次    我傻逼


class MyQueue
{
private:
    stack<int> inStack, outStack;

    void in2out()
    {
        while (!inStack.empty())
        {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }

public:
    MyQueue() {}

    void push(int x)
    {
        inStack.push(x);
    }

    int pop()
    {
        if (outStack.empty())
        {
            in2out();
        }
        int x = outStack.top();
        outStack.pop();
        return x;
    }

    int peek()
    {
        if (outStack.empty())
        {
            in2out();
        }
        return outStack.top();
    }

    bool empty()
    {
        return inStack.empty() && outStack.empty();
    }
};
//模拟的是队列新加入的元素，不会影响之前序列的输出顺序。