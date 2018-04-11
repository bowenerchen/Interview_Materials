/**
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/

/**
 * Definition for singly-preed list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode
struct ListNode* deleteDuplicates(struct ListNode* head) {
    if(head==NULL || head->next==NULL)
        return head;
    NODE* current=head;
    head=NULL;
    NODE* pre=head;
    NODE* temp=NULL;
    NODE* del=NULL;
    int flag=-9999;
    while(current->next){
        if(current->val!=current->next->val){
            temp=current;
            current=current->next;
            temp->next=NULL;
            if(head==NULL){
                head=temp;
                pre=head;
            }else{
                while(pre->next){
                    pre=pre->next;
                }
                pre->next=temp;
                pre=pre->next;
            }
        }else{
            flag=current->val;
            while(current){
                if(current->val==flag){
                    del=current;
                    current=current->next;
                    free(del);
                }else{
                    break;
                }
            }
            if(!current){
                return head;
            }
        }
    }
    if(head==NULL){
        head=current;
        return head;
    }
    if(pre){
        pre->next=current;
    }
    return head;
}
