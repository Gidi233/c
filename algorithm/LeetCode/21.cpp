// struct ListNode
// {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
// };

// class Solution
// {
// public:
//     ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
//     {
//         if (list1 == nullptr && list2 == nullptr)
//             return nullptr;
//         if (list1 == nullptr)
//             return list2;
//         if (list2 == nullptr)
//             return list1;

//         ListNode *ans = new ListNode(0, list1->val <= list2->val ? list1 : list2);
//         if (ans->next == list2)
//             list2 = ans;
//         else
//             list1 = ans;

//         while (list1->next != nullptr && list2->next != nullptr)
//         {
//             ListNode *min = list1->val <= list2->val ? list1 : list2;
//             if (min == list2)
//             { // list1<list2
//                 list2 = list1;
//                 list1 = min;
//             }
//             if (list1->next->val > list2->val)
//             {
//                 ListNode *tmp = list2->next;
//                 list2->next = list1->next;
//                 list1->next = list2;
//                 list1 = list1->next;
//                 list2 = tmp;
//             }
//             else
//             {
//                 list1 = list1->next;
//             }
//         }
//         ListNode *end = (!list1->next) ? list1 : list2;
//         if (end == list2)
//         { // list1==end
//             list2 = list1;
//             list1 = end;
//         }
//         if (list1->val <= list2->next->val)
//         {
//             list1->next = list2->next;
//             list2->next = list1;
//         }
//         else
//         {
//             while (list2->next != nullptr)
//             {
//                 if (list1->val <= list2->next->val)
//                     break;
//                 list2 = list2->next;
//             }
//             list1->next = list2->next;
//             list2->next = list1;
//         }
//         return ans->next;
//     }
// };
// 逻辑不对 有几个测试点改不对

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        if (l1 == nullptr)
        {
            return l2;
        }
        else if (l2 == nullptr)
        {
            return l1;
        }
        else if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};
// 官方递归

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        ListNode *preHead = new ListNode(-1);

        ListNode *prev = preHead;
        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val < l2->val)
            {
                prev->next = l1;
                l1 = l1->next;
            }
            else
            {
                prev->next = l2;
                l2 = l2->next;
            }
            prev = prev->next;
        }

        // 合并后 l1 和 l2 最多只有一个还未被合并完，我们直接将链表末尾指向未合并完的链表即可
        prev->next = l1 == nullptr ? l2 : l1;

        return preHead->next;
    }
};
// 官方迭代
int main()
{
    Solution solution;
    // ListNode l1(-10, new ListNode(-9, new ListNode(-6, new ListNode(-4, new ListNode(1, new ListNode(9, new ListNode(9)))))));
    // ListNode l2(-5, new ListNode(-3, new ListNode(0, new ListNode(7, new ListNode(8, new ListNode(8))))));
    ListNode l1(2);
    ListNode l2(1);

    ListNode *ans = solution.mergeTwoLists(&l1, &l2);
    int i = 0;
}