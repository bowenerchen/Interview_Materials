/*A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
Return a deep copy of the list.*/

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     struct RandomListNode *next;
 *     struct RandomListNode *random;
 * };
 */
 #define NODE struct RandomListNode
struct RandomListNode *copyRandomList(struct RandomListNode *head){
    if(!head) return NULL;
    NODE* current=head;
    NODE* copy=head;
    NODE* nx=current->next;
    NODE* temp=NULL;
    while(current){
        nx=current->next;
        temp=(NODE*)malloc(sizeof(NODE));
        current->next=temp;
        temp->next=nx;
        temp->random=NULL;
        temp->label=current->label;
        current=nx;
    }
    current=head;copy=current->next;
    while(current){
        if(current->random==NULL){
            copy->random==NULL;
        }else{
            copy->random=current->random->next;
        }
        current=current->next->next;
        if(copy->next)
            copy=copy->next->next;
    }
    current=head;copy=current->next;
    NODE* copylist=copy;NODE* pre=current;NODE* pre_cp=copy;
    while(copy){
        if(copy->next==NULL){ 
            if(pre_cp!=copy) 
            pre_cp->next=copy;
            break;
        }else{
            current->next=current->next->next;
            copy->next=copy->next->next;
        }
        pre_cp=copy;
        copy=copy->next;
        pre=current;
        current=current->next;
    }
    current->next=NULL;
return copylist;
}
