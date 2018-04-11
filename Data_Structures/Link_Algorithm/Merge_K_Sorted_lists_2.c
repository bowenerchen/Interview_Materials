/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#define NODE struct ListNode
#define SWAP(a,b,type) {type c=(*a);(*a)=(*b);(*b)=c;}

static void adjustheap(NODE** ele,int index,NODE* point){
      while(index && ((point->val)<(ele[(index-1)/2]->val))){
      	SWAP((&ele[index]),(&ele[(index-1)/2]),NODE**);
      	index=(index-1)/2;
      }
      ele[index]=point;
return ;
}

static void percolatedown(NODE** ele,int index,NODE* point,int size){
	int cmp=point->val;
	int lch;
	while((index*2+1)<=size-1){/*assum has left child*/
		lch=index*2+1;
		/*if also has right child then get the miner one*/
		if(lch+1<=size-1 && (ele[lch+1]->val)<(ele[lch]->val)){
			lch++;
		}
		/*compare to the miner one of the children*/
		if((ele[lch]->val)<cmp){
			(ele[index])=(ele[lch]);
		}else{
			break;
		}
		index=lch;
	}
	ele[index]=point;
return ;
}

static struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    NODE* heap[listsSize];
    int size=0;
    for(int i=0;i<listsSize;i++){
        if(lists[i]){
            adjustheap(heap,size,lists[i]);
            size++;
        }
    }
    
    if(size==0){
        printf("size is 0\n");
        return NULL;
    }
    
    if(size==1){
        printf("size is 1\n");
        return heap[0];
    }

    NODE* head=heap[0];
    NODE* first=heap[0];/*point to the minium node link*/
    NODE* current=head;
    while(size>1){
        if(first->next){
            first=first->next;
            percolatedown(heap,0,first,size);
        }else{
            SWAP(&heap[0],&heap[size-1],NODE**);
            size--;
            percolatedown(heap,0,heap[0],size);
        }
        
        first=heap[0];
        current->next=first;
        current=first;
    }

    return head;
}

