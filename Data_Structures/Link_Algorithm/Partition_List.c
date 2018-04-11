/*Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode
struct ListNode* partition(struct ListNode* head, int x) {
    if(!head || !(head->next)) return head;
    NODE* current=head;NODE* nx=NULL;
    NODE* lest=NULL;NODE* cur_lest=NULL;
    NODE* gert=NULL;NODE* cur_gert=NULL;
    while(current){
        nx=current->next;
        current->next=NULL;
        if(current->val >= x ){
            if(gert==NULL){
                gert=current;
                cur_gert=current;
            }else{
                cur_gert->next=current;
                cur_gert=cur_gert->next;
            }
        }else{
            if(lest==NULL){
                lest=current;
                cur_lest=current;
            }else{
                cur_lest->next=current;
                cur_lest=cur_lest->next;
            }
        }
        current=nx;
    }
    if(lest){
        cur_lest->next=gert;
    }
return lest?lest:gert;
}
