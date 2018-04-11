/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 #define NODE struct ListNode
struct ListNode* insertionSortList(struct ListNode* head) {
    if(!head || !(head->next)) return head;
    NODE* current=NULL;NODE* pre=NULL;
    NODE* border=head;NODE* pre_border=NULL;
    NODE* insert=border->next;
    while(border->next){
        insert=border->next;
        if(border==head){
            if(border->val>=insert->val){
                border->next=insert->next;
                insert->next=border;
                head=insert;
                continue;
            }else{
                border=border->next;
                continue;
            }
        }else{
            current=head;
            while(current!=border){
                if(current==head&& head->val>=insert->val){
                    border->next=insert->next;
                    insert->next=head;
                    head=insert;
                    break;
                }else{
                    pre=current;
                    current=current->next;
                    if(current->val>=insert->val){
                        border->next=insert->next;
                        insert->next=current;
                        pre->next=insert;
                        break;
                    }else{
                        if(current==border){
                            border=border->next;
                            break;
                        }else
                            continue;
                    }
                }
            }
        }
    }
return head;
}
