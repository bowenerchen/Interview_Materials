/*
Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode
 
 static void reverse(NODE* start,NODE* end,NODE** pprenode){
     NODE* border=end->next;
     NODE* current=start;
     NODE* ppre=current;
     NODE* pnext=current->next;
     current->next=pnext->next;
     while(pnext!=border){
         current=pnext;
         pnext=current->next;
         current->next=ppre;
         ppre=current;
     }
     (*pprenode)=current;
     return ;
 }
 
struct ListNode* swapPairs(struct ListNode* head) {
    if(!head || !(head->next)){
        return head;
    }
    NODE* prenode=head;
    NODE* start=head;
    NODE* end=head;
    int count=0;
    while(end){
        while(count<1){
            end=end->next;
            if(!end){
                return head;
            }
            count++;
        }
        NODE* temp=prenode;
        reverse(start,end,&prenode);
        if(temp==head){
            head=prenode;
        }else{
            temp->next=prenode;
        }
        prenode=start;
        start=start->next;
        if(!start){
            return head;
        }
        end=start;
        count=0;
    }
    return head;
}
