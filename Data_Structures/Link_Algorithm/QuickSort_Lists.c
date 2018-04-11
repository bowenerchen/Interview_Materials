/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */ 

/***
    pslow以及pslow左边的节点的val <= 头结点的val
    pslow右边的节点的val > 头结点的val
***/
#define NODE struct ListNode
#define SWAP(a,b,type) {type c=a;a=b;b=c;}
static void quicksort(NODE* phead,NODE* pend){
             if(!phead || !(phead->next) || (phead==pend)){
                 return ;
         }
         NODE* pfast=phead->next;
         NODE* pslow=phead;
         while(pfast!=pend){
                if(pfast->val<phead->val){
                                pslow=pslow->next;
                                 /*if not equal then swap otherwise no necessary*/
                                 if(pslow->val != pfast->val)
                                 SWAP(pslow->val,pfast->val,int);
                 }
               pfast=pfast->next;
         }
         SWAP(pslow->val,phead->val,int);
         quicksort(phead,pslow);
         //quicksort(pslow->next,NULL);
         quicksort(pslow->next,pend);
}
struct ListNode* insertionSortList(struct ListNode* head) {
    quicksort(head,NULL);
return head;
}
