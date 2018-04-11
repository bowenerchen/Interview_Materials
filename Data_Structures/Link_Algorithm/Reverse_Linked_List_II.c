/*
Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ≤ m ≤ n ≤ length of list.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode
static NODE* do_reverse(NODE* pm,NODE* pn){
    NODE* current=pm;
    NODE* nx=NULL;
    NODE* pre=current;
    while(current != pn){
        nx=current->next;
        if(pre==current){
            current->next=pn->next;
        }else{
            current->next=pre;
        }
        pre=current;
        current=nx;
    }
    current->next=pre;
return pn;
}
struct ListNode* reverseBetween(struct ListNode* head, int m, int n){
    if(!head || !(head->next)) return head;
    //if(m==n) return head;
    if(m>=n) return head;
    NODE* pre_m=head;
    NODE* pm=head;
    NODE* pn=head;
    int count=1;
    if(m>1){
        while(count!=m){
            pre_m=pm;
            pm=pm->next;
            count++;
        }
    }
    count=1;
    while(count!=n){
        pn=pn->next;
        count++;
    }
    
    if(m==1){
        head=do_reverse(pm,pn);
    }else{
        pre_m->next=do_reverse(pm,pn);
    }
return head;
}

