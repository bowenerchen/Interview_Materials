/*
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode
void reorderList(struct ListNode* head) {
    if(!head||!(head->next)||(!head->next->next)) 
        return head;
    NODE* slow=head;NODE* fast=slow;
    while(fast->next){
        slow=slow->next;
        fast=fast->next;
        if(fast->next) fast=fast->next;
        if(fast->next==NULL||fast->next->next==NULL)
            break;
    }
    NODE* half=slow->next;
    slow->next=NULL;
    NODE* pre=half;
    NODE* rev=half->next;
    NODE* nx=NULL;
    pre->next=NULL;
    while(rev){
        nx=rev->next;
        rev->next=pre;
        pre=rev;
        rev=nx;
    }
    half=pre;
    NODE* current=head;
    while(half){
        nx=current->next;
        current->next=half;
        half=half->next;
        current=current->next;
        current->next=nx;
        current=nx;
    }
return head;
}
