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