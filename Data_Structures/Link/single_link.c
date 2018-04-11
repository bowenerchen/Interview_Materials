#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    int val;
    struct node* next;
} NODE;

NODE* head;

NODE* gen_node(int val) {
    
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->val = val;
    tmp->next == NULL;
    return tmp;
}

NODE* insert_node(NODE* p_node) {
    if(head == NULL) {
        head = p_node;
        return NULL;
    }
    
    NODE* tmp = head;
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = p_node;

    return tmp->next;
}

void delete_node(int val) {
    
    if(head && (head->val == val) ) {
        NODE* del = head;
        head= head->next;
        printf("delete %d\n", del->val);
        free(del);
        return;
    }

    NODE* tmp = head;
    while(tmp->next && tmp->next->val != val) {
        tmp = tmp->next;
    }

    if(tmp->next == NULL) {
        printf("value %d not exists\n", val);
        return;
    }

    NODE* del = tmp->next;
    tmp->next = tmp->next->next;
    printf("delete %d\n", del->val);
    free(del);
    return;
}

/*
 * 三个指针翻转链表
 * */
void reverse_link(NODE** phead) {
    
    NODE* head = *phead;
    if(head == NULL || head->next == NULL) {
        return ;
    }

    NODE* curr = head;
    NODE* tmp = curr->next;
    NODE* newhead = NULL;

    while(curr != NULL) {
        tmp = curr->next;// 指向下一个节点
        curr->next = newhead;// 当前节点的next指向newhead
        newhead = curr;// 更新newhead
        curr = tmp; // 更新curr
    }
    *phead = newhead;
}

void show_all_nodes() {
    
    NODE* tmp = head;
    int count = 0x00;
    while(tmp) {
        printf("%d ", tmp->val);
        tmp = tmp->next;
        count++;
    }
    printf("\n");
    printf("there are(is) %d nodes\n", count);
    return;
}

void destroy_link() {
    
    NODE* tmp = head;
    while(tmp) {
        delete_node(tmp->val);
        tmp = tmp->next;
    }

    return;
}

int main() {
    
    int i = 0;
    for(i=0; i<10; i++) {
        insert_node(gen_node(i));
    }

    show_all_nodes();

    reverse_link(&head);
    show_all_nodes();

    delete_node(5);
    show_all_nodes();

    delete_node(4);
    show_all_nodes();

    delete_node(3);
    show_all_nodes();

    delete_node(9);
    show_all_nodes();

    delete_node(8);
    show_all_nodes();

    delete_node(1);
    show_all_nodes();

    destroy_link();
    show_all_nodes();
}
