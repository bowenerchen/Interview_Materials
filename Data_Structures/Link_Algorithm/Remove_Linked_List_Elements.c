/*
Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode
struct ListNode* removeElements(struct ListNode* head, int val) {
    if(!head) return NULL;
    NODE* del=NULL;
    NODE* pre=head;
    while(pre){
        if(val==head->val){
            del=head;
            head=head->next;
            free(del);
            pre=head;
            continue;
        }
        while(pre->next){
            if(pre->next->val==val){
                del=pre->next;
                pre->next=pre->next->next;
                free(del);
                //return head;
            }else
            pre=pre->next;
        }
        pre=pre->next;
    }
    
return head;
}
