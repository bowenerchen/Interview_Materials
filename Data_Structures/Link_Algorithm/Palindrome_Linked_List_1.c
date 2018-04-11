/*
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode
 static NODE* kreversal(NODE* start,NODE* end){
	/*after reversal ,the current pointer points to the first element of these k elements*/
	NODE* current=start;
	NODE* ppre=current;
	NODE* pnext=current->next;
	NODE* border=end->next;/*end will change by the last node,so pointer border will store the real end position*/
	current->next=border;
	while(pnext!=border){
		current=pnext;
		pnext=current->next;
		current->next=ppre;
		ppre=current;
	}
	return current;
}
bool isPalindrome(struct ListNode* head) {
    if(!head) return true;
    if(!(head->next)) return true;
    if(head && head->next && !(head->next->next)){
        if(head->val==head->next->val) return true;
        else return false;
    }
    NODE* slow=head;
    NODE* fast=head;
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
    printf("count=%d\n",count);
    NODE* temp=slow;
    slow=slow->next;
    NODE* start=kreversal(head,temp);
    if(count%2){
        start=start->next;
    }
    while(slow){
            printf("slow->%d\n",slow->val);
            printf("start->%d\n",start->val);
            if(slow->val!=start->val){
                return false;
            }
            slow=slow->next;
            start=start->next;
        }
    return true;
}
