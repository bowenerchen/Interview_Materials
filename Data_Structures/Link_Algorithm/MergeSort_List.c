/*
Sort a linked list in O(n log n) time using constant space complexity.
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode
 #define SWAP(a,b,type) {type c=a;a=b;b=c;}
 static NODE* findmiddle(NODE* phead){
         if(!(phead) || !(phead)->next){
                 return (phead);
         }
         NODE* point_middle=(phead);
         NODE* point_double=(phead);
         NODE* before_middle=(phead);
         NODE* head_b=(phead);
         while(point_double && (point_double->next)){
                 point_double=point_double->next->next;
                 before_middle=point_middle;
                 point_middle=point_middle->next;
         }
         before_middle->next=NULL;
         head_b=point_middle;
 return head_b;
 }

 static NODE* dosort(NODE* head_a,NODE* head_b){
         if(!head_a) return head_b;
         else
         if(!head_b) return head_a;
         NODE* current=NULL;
         if(head_a->val < head_b->val){
                 current=head_a;
                 current->next=dosort(head_a->next,head_b);
         }else{
                 current=head_b;
                 current->next=dosort(head_b->next,head_a);
         }
 return current;
 }

 static void mergesort(NODE** phead){
         if(!phead || !(*phead) || !((*phead)->next)){
                 return ;
         }
         NODE* head_a=(*phead);
         NODE* head_b=findmiddle(head_a);
         mergesort(&head_a);
         mergesort(&head_b);
         (*phead)=dosort(head_a,head_b);
 return ;
 }

struct ListNode* sortList(struct ListNode* head) {
    mergesort(&head);
return head;
}
