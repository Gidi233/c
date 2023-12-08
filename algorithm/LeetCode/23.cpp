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
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        int size = lists.size();
        ListNode ans(-1);
        ListNode *cun = &ans;
        bool flag = 1;
        while (flag)
        {
            ListNode *min = nullptr;
            int index = 0;
            flag = 0;
            for (int i = 0; i < size; i++)
            {
                if (lists[i] == nullptr)
                    continue;
                if (!flag)
                {
                    min = lists[i];
                    index = i;
                    flag = 1;
                }
                else if (lists[i]->val < min->val)
                {
                    min = lists[i];
                    index = i;
                }
            }
            if (flag)
            {
                cun->next = min;
                cun = cun->next;
                lists[index] = lists[index]->next;
            }
        }
        return ans.next;
    }
};
// 我这是个傻呗的k*k*n;

class Solution
{
public:
    // struct comp
    // {
    //     bool operator()(ListNode *a, ListNode *b)
    //     {
    //         return a->val > b->val;
    //     }
    // };
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        lists.erase(remove_if(lists.begin(), lists.end(), [](auto p)
                              { return !p; }),
                    lists.end());
        // auto cmp = [](auto &a, auto &b)
        // { return a->val > b->val; };
        // priority_queue<ListNode *, vector<ListNode *>,decltype(cmp)> q(cmp, lists);不用推导的话
        priority_queue q{[](auto &a, auto &b)
                         { return a->val > b->val; },
                         lists};
        // priority_queue<ListNode *, vector<ListNode *>, comp> q(lists.begin(), lists.end());另一个等价的
        ListNode head;
        for (auto p = &head; !q.empty(); q.pop())
        {
            p = p->next = q.top();
            if (p->next)
                q.push(p->next);
        }
        return head.next;
    }
};
// 用优先队列，这个用了使用C++17的推导指引，更方便更优雅，避免污染变量名。
// 可以不用给模板传类型，直接通过传参推导出类型
// 还可以主动添加推导规则
// A(const char *) -> A<std::string>;
// A(bool) -> A<int>;
// A(int) -> A<char>;

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *a, ListNode *b)
    {
        if ((!a) || (!b))
            return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr)
        {
            if (aPtr->val < bPtr->val)
            {
                tail->next = aPtr;
                aPtr = aPtr->next;
            }
            else
            {
                tail->next = bPtr;
                bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode *merge(vector<ListNode *> &lists, int l, int r)
    {
        if (l == r)
            return lists[l];
        if (l > r)
            return nullptr;
        int mid = (l + r) >> 1;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        return merge(lists, 0, lists.size() - 1);
    }
};
// 通过分治，把要合并的长度（平均）缩短， O(kn×log⁡k)空间复杂度为 O(logk)