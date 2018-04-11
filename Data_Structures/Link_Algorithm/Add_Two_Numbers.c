/*
You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    if(l1==NULL) return l2;
    else
    if(l2==NULL) return l1;
    int num=0;
    int up=0;
    NODE* head=l1;
    NODE* current=l1;
    NODE* pre=NULL;
    while(current){
        if(l1 && l2){
            current=l1;
            num=l1->val+l2->val+up;
        }else{
            current=l1?l1:l2;
            if(current!=NULL && current!=pre->next){
                pre->next=current;
            }else if(current==NULL && up==1){
                pre->next=(NODE*)malloc(sizeof(NODE));
                current=pre->next;
                current->val=up;
                current->next=NULL;
                break;
            }else if(current==NULL && up==0){
                break;
            } 
            num=current->val+up;
        }
        if(num>=10){
            num=num%10;
            up=1;
        }else{
            up=0;
        }
        current->val=num;
        pre=current;
        if(l1)
            l1=l1->next;
        if(l2)
            l2=l2->next; 
    }
return head;
}
