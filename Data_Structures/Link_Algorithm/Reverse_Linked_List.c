/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode
struct ListNode* reverseList(struct ListNode* head) {
    		if(!(head)|| !(head->next)){
			//printf("empty link\n");
			return head;
		}else{
			NODE* current=(head);/*point to node 1*/
			NODE* ppre=current;/*point to node 1*/
			NODE* pnext=current->next;/*point to node 2*/
			current->next=NULL;/*node 1 next points to NULL*/
			while(pnext){/*if node 2 exists*/
				current=pnext;/*point to node 2*/
				pnext=current->next;/*get node 3*/
				current->next=ppre;/*node 2 point  to node 1*/
				ppre=current;/*get node 2*/
			}
			(head)=current;/*make head point to the last node*/
		}
return head;
}
