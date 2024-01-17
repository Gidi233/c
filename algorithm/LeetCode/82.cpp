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
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (!head || !head->next)
            return head;
        ListNode *fast = head, dummy(0, head), *cun = &dummy;
        while (1)
        {
            if (!fast->next)
            {
                if (fast == cun->next)
                    cun->next = fast;
                else
                    cun->next = nullptr;
                break;
            }
            if (fast->next->val != fast->val)
            {
                if (cun->next == fast)
                {
                    cun->next = fast;
                    cun = cun->next;
                }
                else
                    cun->next = fast->next;
            }
            fast = fast->next;
        }
        return dummy.next;
    }
};

class Solution
{
public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        if (!head)
        {
            return head;
        }

        ListNode *dummy = new ListNode(0, head);

        ListNode *cur = dummy;
        while (cur->next && cur->next->next)
        {
            if (cur->next->val == cur->next->next->val)
            {
                int x = cur->next->val;
                while (cur->next && cur->next->val == x)
                {
                    cur->next = cur->next->next;
                }
            }
            else
            {
                cur = cur->next;
            }
        }

        return dummy->next;
    }
};

// 官方题解