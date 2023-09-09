/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution
{
private:
    void reverseLinkedList(ListNode *head)
    {
        // 也可以使用递归反转一个链表
        ListNode *pre = nullptr; // 记录一下上一个节点，让当前的下一个指向上一个
        ListNode *cur = head;

        while (cur != nullptr)
        {
            ListNode *next = cur->next; // 记录下一个节点
            cur->next = pre;
            pre = cur;
            cur = next;
        }
    }

public:
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        // 因为头节点有可能发生变化，使用虚拟头节点可以避免复杂的分类讨论
        ListNode *dummyNode = new ListNode(-1);
        dummyNode->next = head;

        ListNode *pre = dummyNode;
        // 第 1 步：从虚拟头节点走 left - 1 步，来到 left 节点的前一个节点
        // 建议写在 for 循环里，语义清晰
        for (int i = 0; i < left - 1; i++)
        {
            pre = pre->next;
        }

        // 第 2 步：从 pre 再走 right - left + 1 步，来到 right 节点
        ListNode *rightNode = pre;
        for (int i = 0; i < right - left + 1; i++)
        {
            rightNode = rightNode->next;
        }

        // 第 3 步：切断出一个子链表（截取链表）
        ListNode *leftNode = pre->next;
        ListNode *curr = rightNode->next;

        // 注意：切断链接
        pre->next = nullptr;
        rightNode->next = nullptr;

        // 第 4 步：同第 206 题，反转链表的子区间
        reverseLinkedList(leftNode);

        // 第 5 步：接回到原来的链表中
        pre->next = rightNode;
        leftNode->next = curr;
        return dummyNode->next;
    }
};
// 因为给出的头也可能被翻转，所以建一个虚拟节点

class Solution
{
public:
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        // 因为头节点有可能发生变化，使用虚拟头节点可以避免复杂的分类讨论
        ListNode *dummyNode = new ListNode(-1);
        dummyNode->next = head;

        ListNode *pre = dummyNode;
        // 第 1 步：从虚拟头节点走 left - 1 步，来到 left 节点的前一个节点
        for (int i = 0; i < left - 1; i++)
        {
            pre = pre->next;
        }

        ListNode *rightnode = pre->next;
        ListNode *cur = pre->next->next;
        for (int i = 0; i < right - left; i++)
        {
            ListNode *next = cur->next;
            ListNode *temp = pre->next;
            pre->next = cur;
            cur->next = temp;
            cur = next;
        }
        rightnode->next = cur;
        return dummyNode->next;
    }
};
// 把要翻转的范围头插到左节点的左边，就可以翻转

// 递归反转整个链表
ListNode reverse(ListNode head)
{
    if (head.next == null)
        return head;
    ListNode last = reverse(head.next);
    head.next.next = head;
    head.next = null;
    return last;
}

// 反转链表前 N 个节点
ListNode successor = null; // 后驱节点

// 反转以 head 为起点的 n 个节点，返回新的头结点
ListNode reverseN(ListNode head, int n)
{
    if (n == 1)
    {
        // 记录第 n + 1 个节点
        successor = head.next;
        return head;
    }
    // 以 head.next 为起点，需要反转前 n - 1 个节点
    ListNode last = reverseN(head.next, n - 1);

    head.next.next = head;
    // 让反转之后的 head 节点和后面的节点连起来
    head.next = successor;
    return last;
}

// 翻转一个区间
ListNode reverseBetween(ListNode head, int m, int n)
{
    // base case
    if (m == 1)
    {
        return reverseN(head, n);
    }
    // 前进到反转的起点触发 base case
    head.next = reverseBetween(head.next, m - 1, n - 1);
    return head;
}
