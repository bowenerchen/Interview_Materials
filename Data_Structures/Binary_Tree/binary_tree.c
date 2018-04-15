#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

typedef struct node {
    int val;
    struct node* left;
    struct node* right;
} NODE;

static NODE* head = NULL;

NODE* gen_node(int val) {
    NODE* tmp = (NODE*)malloc(sizeof(NODE));
    tmp->val = val;
    tmp->left = NULL;
    tmp->right = NULL;
return tmp;
}

/***
 * 二叉树在插入节点的时候会遵循一个原则，就是利用节点的值来判断
 * 从根节点开始往下走，
 * 比当前节点小（或等于）的会被插入到当前节点的左边，
 * 比当前节点大的会被插入到当前节点的右边
 * ***/
void insert_node(NODE** cur, NODE* pnode) {
    if(pnode == NULL) {
        printf("pnode == NULL\n");
        return;
    }

    if(*cur == NULL) {
        *cur = pnode;
        if(cur == &head) {
            printf("insert head node %d\n", pnode->val);
        } else {
            printf("insert node %d\n", pnode->val);
        }
        return;
    } else if(pnode->val > (*cur)->val) {
        insert_node(&((*cur)->right), pnode); //大的值放到右边
    } else {
        insert_node(&((*cur)->left), pnode); //小的值放到左边
    }
return;
}

//最大子节点在最右边
NODE* find_max(NODE* pnode) {
    if(pnode == NULL)
        return NULL;

    while(pnode->right) {
        pnode = pnode->right;
    }

    return pnode;
}

//最小子节点在最左边
NODE* find_min(NODE* pnode) {
    
    if(pnode == NULL) {
        return NULL;
    }
    
    while(pnode->left) {
        pnode = pnode->left;
    }

    return pnode;
}

/***
 * 被删除的节点是叶子节点
 * 被删除的节点只有左孩子节点
 * 被删除的节点只有右孩子节点
 * 被删除的有两个孩子节点
 *
 * 1.被删除的节点是叶子节点，这时候只要把这个节点删除，再把指向这个节点的父节点指针置为空就行
 *
 * 2.被删除的节点有左子树，或者有右子树，而且只有其中一个，那么只要把当前删除节点的父节点指向被删除节点的左子树或者右子树就行。
 *
 * 3.被删除的节点既有左子树而且又有右子树，这时候需要把左子树的最右边的节点或者右子树最左边的节点提到被删除节点的位置，为什么要这样呢，根据二叉查找树的性质，父节点的指针一定比所有左子树的节点值大而且比右子树的节点的值小，为了删除父节点不破坏二叉查找树的平衡性，应当把左子树最大的节点或者右子树最小的节点放在父节点的位置，这样的话才能维护二叉查找树的平衡性。（我是找的右子树的最小节点）
 * ***/
void del_node(NODE** cur, int val) {
    
    if(*cur == NULL) {
        printf("%d not exists\n", val);
        return;
    }
   
    //printf("now root is %d, del val is %d\n", (*cur)->val, val); 

    if((*cur)->val > val) { //被删除的值更小，则在左子树上

        del_node(&((*cur)->left), val);

    } else if((*cur)->val < val) { //被删除的值更大，则在右子树上

        del_node(&((*cur)->right), val);

    } else if((*cur)->val == val) { //找到了要删除的节点
        
        //printf("match %d\n", val);
        NODE* tmp = *cur;
        NODE* del = NULL;
        if(tmp->left == NULL && tmp->right == NULL) { // 被删除的点是叶子节点
            
            //printf("del leaf node\n"); 
            del = tmp;
            *cur = NULL;//将其父节点的这个指针置为NULL
            free(del);//删除这个叶子节点
            return;

        }else if(tmp->left != NULL && tmp->right != NULL){ //被删除的节点有两个子节点
        
            //printf("two children\n");
            //把左子树最大的节点或者右子树最小的节点放在父节点的位置
            NODE* pmax = find_max(tmp->left); //找左子树的最大节点
            //printf("node %d max left children is %d\n", tmp->val, pmax->val);
            tmp->val = pmax->val;
            del_node(&((*cur)->left), pmax->val);

        } else if(tmp->left != NULL || tmp->right != NULL) { //被删除的节点有一个子节点
            
            //printf("one children\n");
            if(tmp->left) { //仅有左子树
            
                //printf("left children\n");
                del = tmp;
                *cur = tmp->left;
                free(del);
                return;

            } else if(tmp->right) { //仅有右子树
                
                //printf("right children\n");
                del = tmp;
                *cur = tmp->right;
                free(del);
                return;
            }

        }

    }
    
}

void pre_show(NODE* pnode) {
    if(pnode == NULL) {
        return;
    }
    printf("%d ", pnode->val);
    pre_show(pnode->left);
    pre_show(pnode->right);
return;
}

void mid_show(NODE* pnode) {
    if(pnode == NULL) {
        return;
    }

    mid_show(pnode->left);
    printf("%d ", pnode->val);
    mid_show(pnode->right);
return;
}

void post_show(NODE* pnode) {
    if(pnode == NULL) {
        return;
    }

    post_show(pnode->left);
    post_show(pnode->right);
    printf("%d ", pnode->val);
}

void destroy_tree() {
    while(head) {
        del_node(&head, head->val);
    }
}

int tree_depth(NODE* pnode) {
    
    if(pnode == NULL) {
        return 0;
    }

    int left_depth = tree_depth(pnode->left);
    int right_depth = tree_depth(pnode->right);

    return left_depth > right_depth ? left_depth+1 : right_depth+1;
}

int main() {
    int a[10] = {5,3,6,4,7,2,8,1,0,9};
    for(int i = 0; i < sizeof(a)/sizeof(int); i++) {
        insert_node(&head, gen_node(a[i]));
    }

    pre_show(head);
    printf("depth is %d\n", tree_depth(head));

    del_node(&head, 3);
    pre_show(head);
    printf("depth is %d\n", tree_depth(head));

    del_node(&head, 6);
    pre_show(head);
    printf("depth is %d\n", tree_depth(head));

    del_node(&head, 5);
    pre_show(head);
    printf("depth is %d\n", tree_depth(head));

    del_node(&head, 0);
    pre_show(head);
    printf("depth is %d\n", tree_depth(head));

    del_node(&head, 9);
    pre_show(head);
    printf("depth is %d\n", tree_depth(head));

    del_node(&head, 10);
    pre_show(head);
    printf("depth is %d\n", tree_depth(head));

    printf("=====\n");
    destroy_tree();
}
