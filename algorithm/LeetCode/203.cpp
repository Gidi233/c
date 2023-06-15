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

//�������ݽṹ��ѭ��������������ѭ���ж�ͷ�ڵ�򴴽�һ���ڵ��next��ͷ��㡣

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

//�ݹ�ķ�����ͦ�ɵģ��е���˼