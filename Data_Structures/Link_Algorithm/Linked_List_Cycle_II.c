/*
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
Note: Do not modify the linked list.
Follow up:
Can you solve it without using extra space?*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode
struct ListNode *detectCycle(struct ListNode *head) {
    if(!head|| !(head->next)) return NULL;
    NODE* slow=head;NODE* fast=head;NODE* meet=NULL;
    int count_slow=0;int count_ring=0;
    while(fast->next){
        slow=slow->next;count_slow++;
        fast=fast->next;
        if(fast->next) fast=fast->next;
        if(fast->next==NULL || fast->next->next==NULL)
            return NULL;
        if(slow==fast){ 
            meet=slow;
            break;
        }
    }
    while(slow){
        slow=slow->next;count_ring++;
        if(slow==meet){
            break;
        }
    }
    NODE* start=head;slow=meet;
    int dis=count_ring-count_slow;
    if(dis<0){
        for(int i=0;i<(0-dis);i++)
            start=start->next;
    }else{
        for(int i=0;i<dis;i++)
            slow=slow->next;
    }
    while(slow!=start){
        slow=slow->next;
        start=start->next;
    }
return slow;
}

