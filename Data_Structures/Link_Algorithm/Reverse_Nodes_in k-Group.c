/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
#define NODE struct ListNode
static NODE* kreversal(NODE* start,NODE* end){
	/*after reversal ,the current pointer points to the first element of these k elements*/
	NODE* current=start;
	NODE* ppre=current;
	NODE* pnext=current->next;
	NODE* border=end->next;/*end will change by the last node,so pointer border will store the real end position*/
	current->next=border;
	while(pnext!=border){
		current=pnext;
		pnext=current->next;
		current->next=ppre;
		ppre=current;
	}
	return current;
}
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if(!(head)||(!(head)->next)||k<=1){
		return head;
	}
	int count=0;
	NODE* start=(head);
	NODE* end=start;
	/*prefirstnode stores the node or pointer before start node*/
	NODE* prefirstnode=(head);
	while(end){
		while(count<k-1){/*count to  the end position but if to the real link end ,just return and do nothing*/
			end=end->next;
			count++;
			if(!end){
				return head;
			}
		}
		/*at the first ,there is just a head pointer points to the first node */
		if(prefirstnode==(head)){
			/*so the head pointer will points to the new first node */
			(head)=kreversal(start,end);
		}else{
			prefirstnode->next=kreversal(start,end);
		}
		/*cause pointer start will change by the node it points,so after kreversal(...),start now points to the same node but not at the first position,oppoist,the last position of k elements,so,for the next k elements,the prefirstnode->next points to the first of those new k elements*/
		prefirstnode=start;
		start=start->next;/*go on*/
		if(!start){/*it may run to the end of this link,so do nothing*/
			return head;
		}
		end=start;
		count=0;
	}
	return head;
}
