class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr)
            return nullptr;
        if (head->next == nullptr)
            return head;
        ListNode *last = head;
        ListNode *node = head->next;
        ListNode *next = head->next->next;
        last->next = nullptr;

        while (1)
        {
            node->next = last;
            if (next == nullptr)
                break;
            last = node;
            node = next;
            next = next->next;
        }
        return node;
    }
};
// 感觉我写的好烂

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;
        while (curr)
        {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};
// 官方题解

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode *newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};
// 递归