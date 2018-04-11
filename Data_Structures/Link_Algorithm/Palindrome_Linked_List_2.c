/*Given a singly linked list, determine if it is a palindrome.
Follow up:
Could you do it in O(n) time and O(1) space?*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode
bool isPalindrome(struct ListNode* head) {
    if(!head) return true;
    if(!(head->next)) return true;
    if(head && head->next && !(head->next->next)){
        if(head->val==head->next->val) return true;
        else return false;
    }
    NODE* slow=head;NODE* fast=head;
    int count=1;
    while(fast->next){
        fast=fast->next;
        if(fast->next){ 
            fast=fast->next;
            slow=slow->next;
            count++;
            if(fast->next==NULL){
                count=count*2-1;
                break;
            }
        }else{
            count=(count)*2;
            break;
        }
    }
    NODE* start=head;
    NODE* half=NULL;
    NODE* nx=slow->next;
    slow->next=NULL;
    slow=nx;
    while(slow){
        nx=slow->next;
        if(!half){
            half=slow;
            slow->next=NULL;
        }else{
            NODE* temp=half;
            half=slow;
            slow->next=temp;
        }
        slow=nx;
    }
    while(half){
        printf("half->%d\n",half->val);
        printf("start->%d\n",start->val);
        if(half->val!=start->val)
            return false;
        half=half->next;
        start=start->next;
    }
    return true;
}
