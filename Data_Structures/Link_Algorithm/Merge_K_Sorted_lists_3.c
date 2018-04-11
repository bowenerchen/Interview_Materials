/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode

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

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if(!lists)
    	return NULL;
    NODE* head=lists[0];
    for(int i=1;i<listsSize;i++){
        head=dosort(lists[i],head);        
    }
return head;
}
