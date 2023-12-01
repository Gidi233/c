/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *low = head, *fast = head;
        while (1)
        {
            int i = 2;
            while (fast != nullptr && i--)
            {
                fast = fast->next;
                if (fast == low)
                    return 1;
            }
            if (fast == nullptr)
                return 0;
            low = low->next;
        }
    }
};
// 快慢指针

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        unordered_set<ListNode *> seen;
        while (head != nullptr)
        {
            if (seen.count(head))
            {
                return true;
            }
            seen.insert(head);
            head = head->next;
        }
        return false;
    }
};
// 哈希表