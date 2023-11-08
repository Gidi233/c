#include <bits/stdc++.h>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *reverse(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *ans = reverse(head->next);
        head->next->next = head;
        head->next = nullptr;
        return ans;
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *headnode = head, *nextnode = head, *tailnode;
        ListNode *ans = new ListNode(0, head), *prevnode = ans;
        while (1) // nextnode != nullptr
        {
            int i = 0;
            for (i = 0; i < k && nextnode != nullptr; i++)
            {
                if (i == k - 1)
                    tailnode = nextnode;
                nextnode = nextnode->next;
            }
            if (i < k)//不足k个
                break;
            prevnode->next = tailnode;

            tailnode->next = nullptr;
            reverse(headnode);
            headnode->next = nextnode;
            prevnode = headnode;
            headnode = nextnode;
        }
        return ans->next;
    }
};
// 在前面加一个哨兵节点 保持结构一样 可以减少很多特判

class Solution
{
public:
    // 翻转一个子链表，并且返回新的头与尾
    pair<ListNode *, ListNode *> myReverse(ListNode *head, ListNode *tail)
    {
        ListNode *prev = tail->next;
        ListNode *p = head;
        while (prev != tail)
        {
            ListNode *nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }

    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *hair = new ListNode(0);
        hair->next = head;
        ListNode *pre = hair;

        while (head)
        {
            ListNode *tail = pre;
            // 查看剩余部分长度是否大于等于 k
            for (int i = 0; i < k; ++i)
            {
                tail = tail->next;
                if (!tail)
                {
                    return hair->next;
                }
            }
            ListNode *nex = tail->next;
            // 这里是 C++17 的写法，也可以写成
            // pair<ListNode*, ListNode*> result = myReverse(head, tail);
            // head = result.first;
            // tail = result.second;
            tie(head, tail) = myReverse(head, tail);
            // 把子链表重新接回原链表
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
        }

        return hair->next;
    }
};
// 官答
// 本质还是记录上一个（尾）、当前（头和尾）和下一个（头）
int main()
{
    Solution solution;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    ListNode *ans = solution.reverseKGroup(head, 2);
}