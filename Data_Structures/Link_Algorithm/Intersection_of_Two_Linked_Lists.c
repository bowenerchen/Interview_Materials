/*Write a program to find the node at which the intersection of two singly linked lists begins.
For example, the following two linked lists:
A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.
Notes:
If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if(!headA || !headB) return NULL;
    NODE* tempA=headA;NODE* tempB=headB;
    int countA=1;int countB=1;
    while(tempA||tempB){
        if(tempA->next){
            tempA=tempA->next;
            countA++;
        }
        if(tempB->next){
            tempB=tempB->next;
            countB++;
        }
        if(!tempA->next && !tempB->next)
            break;
    }
    int dis=countA-countB;
    if(dis>0){
        for(int i=0;i<(dis);i++){
            headA=headA->next;
        }
    }else if(dis<0){
        for(int i=0;i<(0-dis);i++){
            headB=headB->next;
        }
    }
    while(headA!=headB){
        headA=headA->next;
        headB=headB->next;
    }
return (headA==NULL)?NULL:headA;
}
