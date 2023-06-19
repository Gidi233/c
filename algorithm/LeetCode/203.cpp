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
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if(head==nullptr) return head;
        while(head->val==val){
            head=head->next;
            if(head==nullptr) return head;
        }
        ListNode* prev=head;
        ListNode* head_=head->next;
        while(head_!=nullptr){
            if(head_->val==val){
                prev->next=head_->next;
                head_=head_->next;
            }    
            else{
                prev=head_;
                head_=head_->next;
            }        
        }
        return head;
    }
};

//就是数据结构，循环迭代操作链表，循环判断头节点或创建一个节点的next是头结点。

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr) {
            return head;
        }
        head->next = removeElements(head->next, val);
        return head->val == val ? head->next : head;
    }
};

//递归的方法，挺巧的，有点意思