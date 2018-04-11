/*
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

Subscribe to see which companies asked this question

Show Tags
Show Similar Problems
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode 
 
 static NODE* findlastkth(NODE* head,int k){
     if(!head){
         return NULL;
     }
     if(!k)
        return head;
     if(k==1){
         while(head->next){
             head=head->next;
         }
         return head;
     }
     int count=1;
     NODE* slow=head;
     NODE* fast=head;
     while(count!=k){
         if(fast->next){
             fast=fast->next;
             count++;
         }else{
             return findlastkth(head,k%count);
         }
     }
     while(fast->next){
         fast=fast->next;
         slow=slow->next;
     }
return slow;
 }
 
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if(!head || !(head->next)){
        return head;
    }
    if(k==0){
        return head;
    }
    NODE* kth=findlastkth(head,k);
//    printf("last kth is %d\n",kth->val);
    NODE* begin=head;
    head=kth;
//    printf("head points to %d\n",head->val);
    NODE* temp=head;
    while(temp->next){
        temp=temp->next;
    }
    temp->next=begin;
//    printf("now %d points to %d",temp->val,begin->val);
    while(begin->next!=head){
        begin=begin->next;
    }
    begin->next=NULL;
 //   printf("%d is the last one\n",begin->val);
return head;
}
