/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    NODE* head=NULL;
    NODE* current=NULL;
    NODE* insert=NULL;
    NODE* temp=NULL;
    NODE* temp_ins=NULL;
    if(!(l1 && l2)){
        head=l1?l1:l2;
        return head;
    }else{
        current=(l1->val)<=(l2->val)?l1:l2;
        insert=(current==l1)?l2:l1;
        head=current;
        while(insert){
            if((current->val) <= (insert->val)){
                if(!(current->next) || ((current->next->val)>=(insert->val))){
                    temp=current->next;
                    temp_ins=insert->next;
                    current->next=insert;
                    insert->next=temp;
                    current=insert;
                    insert=temp_ins;
                }else{
                    current=current->next;
                }
            }
        }
    }
return head;
}
