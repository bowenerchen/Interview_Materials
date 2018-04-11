/*
Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode 
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    if(!head){
        return NULL;
    }
    if(!(head->next) && n>=1){
        NODE* del=head;
        head=NULL;
        free(del);
        return NULL;
    }
    //NODE* pre= findlastkth(head,n+1);
    NODE* pre=NULL;
    NODE* del=NULL;
    
    int count=1;
    NODE* slow=head;
    NODE* fast=head;
    while(count!=n+1){
        if(fast->next){
            fast=fast->next;
            count++;
        }else{
                del=head;
                head=head->next;
                free(del);
                return head;
        }
    }
    while(fast->next){
         fast=fast->next;
         slow=slow->next;
     }
    pre=slow;
    del=pre->next;
    pre->next=del->next;
    if(del){
        free(del);
    }
    return head;
}
