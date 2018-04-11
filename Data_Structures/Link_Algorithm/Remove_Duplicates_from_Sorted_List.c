/**
Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode* current=head;
    struct ListNode* del=NULL;
    while(current && current->next){
        if(current->val==current->next->val){
            del=current->next;
            current->next=current->next->next;
            free(del);
            continue;
        }
        current=current->next;
    }
    return head;
}
