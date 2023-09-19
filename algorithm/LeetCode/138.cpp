/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (!head)
            return head;
        Node *had = head;
        unordered_map<Node *, int> raw;
        Node *now[1003] = {};
        raw.emplace(head, 0);
        Node *nod = new Node(head->val);
        Node *cun = nod;
        Node *ans = cun;
        now[0] = cun;
        int i = 1;
        while (had->next)
        {
            raw.emplace(had->next, i);
            now[i] = new Node(had->next->val);
            cun->next = now[i];
            cun = cun->next;
            had = had->next;
            i++;
        }
        had = head;
        cun = ans;
        while (had)
        {
            if (raw.count(had->random))
                cun->random = now[raw[had->random]];
            had = had->next;
            cun = cun->next;
        }
        return ans;
    }
};
// 记录原链表每一个节点的下标，和新建链表每一个下标对应的节点，先建表，再循环一次从原表的map取下标，用下表得到节点赋给random

class Solution
{
public:
    unordered_map<Node *, Node *> cachedNode;

    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        if (!cachedNode.count(head))
        {
            Node *headNew = new Node(head->val);
            cachedNode[head] = headNew;
            headNew->next = copyRandomList(head->next);
            headNew->random = copyRandomList(head->random);
        }
        return cachedNode[head];
    }
};
// 原表新表的下标一一对应，为了防止重复拷贝，我们需要首先检查当前节点是否被拷贝过，如果已经拷贝过，我们可以直接从哈希表中取出拷贝后的节点的指针并返回即可。
// 如果这两个节点中的任何一个节点的新节点没有被创建，我们都立刻递归地进行创建。（实际上也是先建了表，再给random赋值）

class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        for (Node *node = head; node != nullptr; node = node->next->next)
        {
            Node *nodeNew = new Node(node->val);
            nodeNew->next = node->next;
            node->next = nodeNew;
        }
        for (Node *node = head; node != nullptr; node = node->next->next)
        {
            Node *nodeNew = node->next;
            nodeNew->random = (node->random != nullptr) ? node->random->next : nullptr;
        }
        Node *headNew = head->next;
        for (Node *node = head; node != nullptr; node = node->next)
        {
            Node *nodeNew = node->next;
            node->next = node->next->next; // 还原原链表
            nodeNew->next = (nodeNew->next != nullptr) ? nodeNew->next->next : nullptr;
        }
        return headNew;
    }
};
// 通过在原链表的每一个节点后再复制一个，就不用用一个map来存对应的节点（下标），原链表的random->next就是新链表的random，再重新给两个链表的next重新赋值