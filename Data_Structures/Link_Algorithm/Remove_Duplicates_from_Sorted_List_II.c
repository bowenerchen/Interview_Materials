/**
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode

struct ListNode* deleteDuplicates(struct ListNode* head) {
    if(head==NULL || head->next==NULL)
        return head;
    struct ListNode* p = head;
    while(p->next!=NULL && p->val == p->next->val){
        p=p->next;
    }

    if(p!=head){
        while(head!=p->next)
        {
            struct ListNode * tmp = head;
            head=head->next;
            free(tmp);
        }
        return deleteDuplicates(head);
    }

    head->next=deleteDuplicates(head->next);
    return head;
}
