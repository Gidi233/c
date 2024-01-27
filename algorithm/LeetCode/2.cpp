class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *head = new ListNode((l1->val + l2->val) % 10), *last = head;
        bool f = (l1->val + l2->val) / 10;
        l1 = l1->next;
        l2 = l2->next;
        while (l1 && l2)
        {
            last->next = new ListNode((l1->val + l2->val + f) % 10);
            last = last->next;
            f = (l1->val + l2->val + f) / 10;
            l1 = l1->next;
            l2 = l2->next;
        }
        while (l1)
        {
            last->next = new ListNode((l1->val + f) % 10);
            last = last->next;
            f = (l1->val + f) / 10;
            l1 = l1->next;
        }
        while (l2)
        {
            last->next = new ListNode((l2->val + f) % 10);
            last = last->next;
            f = (l2->val + f) / 10;
            l2 = l2->next;
        }
        if (f)
            last->next = new ListNode(1);
        return head;
    }
};
// 模拟
class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *head = nullptr, *tail = nullptr;
        int carry = 0;
        while (l1 || l2)
        {
            int n1 = l1 ? l1->val : 0;
            int n2 = l2 ? l2->val : 0;
            int sum = n1 + n2 + carry;
            if (!head)
            {
                head = tail = new ListNode(sum % 10);
            }
            else
            {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            carry = sum / 10;
            if (l1)
            {
                l1 = l1->next;
            }
            if (l2)
            {
                l2 = l2->next;
            }
        }
        if (carry > 0)
        {
            tail->next = new ListNode(carry);
        }
        return head;
    }
};

// 官方题解