#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    int val;
    struct node* pre;
    struct node* next;
} NODE;

static NODE* head = NULL;

NODE* gen_node(int val) {
    NODE* pnode = (NODE*)malloc(sizeof(NODE));

    if(pnode == NULL) {
        printf("err on pnode\n");
        return NULL;
    }
    pnode->val = val;
    pnode->pre = NULL;
    pnode->next = NULL;
    
return pnode;
}

void insert_node(NODE* pnode) {
    
    if(pnode == NULL) {
        printf("pnode == NULL\n");
        return;
    }

    if(head == NULL) {
        head = pnode;
        pnode->pre = head;
        pnode->next = NULL;

        printf("insert %d,", pnode->val);
        if(pnode->pre == head) {
            printf("pre is head\n");
        }else{
            printf("pre is %d\n",pnode->pre->val);
        }
        return;
    }
        
    NODE* tmp = head;
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = pnode;
    pnode->pre = tmp;
    pnode->next = NULL;
    
    printf("insert %d,", pnode->val);
    printf("pre is %d\n",pnode->pre->val);
    return;
}

void del_node(int val) {

    NODE* tmp = head;
    if(tmp == NULL) {
        printf("empty\n");
        return;
    }

    // 删除第一个节点
    if(tmp->val == val) {
        head = tmp->next;
        //需要进行判断
        //删除的是否是最后一个节点
        if(tmp->next !=NULL ) {
            tmp->next->pre = head;
        }
        printf("del %d\n",val);
        free(tmp);
        return;
    }

    // 删除非第一个节点
    while(tmp->next != NULL && tmp->next->val != val) {
        tmp = tmp->next;
    }
    
    if(tmp->next == NULL) {
        printf("val %d not exists\n", val);
        return;
    }

    NODE* del = tmp->next;
    tmp->next = del->next;
    //需要进行判断
    //是否删除的是最后一个节点
    if(del->next != NULL) {
        del->next->pre = tmp;
    }
    printf("del %d\n",val);
    free(del);
    return;
}

void show() {
    NODE* tmp = head;
    while(tmp) {

        printf("curr=%d ",tmp->val);
        
        if(tmp == head) {
            printf("pre=head ");
        } else {
            printf("pre=%d ",tmp->pre->val);
        }

        if(tmp->next != NULL) {
            printf("next=%d\n",tmp->next->val);
        }else{
            printf("next=NULL\n");
        }

        tmp = tmp->next;
    }

return;
}

void destroy(){
    NODE* tmp = head;
    while(tmp) {
        del_node(tmp->val);
        tmp = head;
    }
    return;
}

int main() {
    for(int i = 0; i < 10; i++) {
        insert_node(gen_node(i));
    }

    show();

    del_node(9);
    del_node(5);
    del_node(15);
    show();

    destroy();

return 0;
}
