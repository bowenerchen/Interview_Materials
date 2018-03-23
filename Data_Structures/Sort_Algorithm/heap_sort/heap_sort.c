#include "../include/common.h"

/***
 * 堆是具有以下性质的完全二叉树：
 * 每个结点的值都大于或等于其左右孩子结点的值，称为大顶堆；
 * 大顶堆：arr[i] >= arr[2i+1] && arr[i] >= arr[2i+2]  
 *
 * 每个结点的值都小于或等于其左右孩子结点的值，称为小顶堆。
 * 小顶堆：arr[i] <= arr[2i+1] && arr[i] <= arr[2i+2]
 *
 * 堆排序是一种不稳定的排序，最优/最坏/平均时间复杂度都为O(nlogn)
 * 建堆的核心内容是调整堆，使二叉树满足堆的定义（每个节点的值都不大于其父节点的值）。
 * 调堆的过程应该从最后一个非叶子节点开始，
 * 假设数组中有N个元素，那么首先最后一个非叶子节点为第N/2个元素
 * ***/

void build_max_heap(int* array, int root_index, int len) {

    if(array == NULL || len <= 0 
            || root_index > len || root_index < 0) {
        return;
    }

    int right_border = len - 1;
    int left_child = 2 * root_index + 1;
    int right_child = 2 * root_index + 2;
    int max_index = root_index;

    /*在根节点，左子叶，右子叶中选择最大的值，放到根节点的位置上*/
    if(left_child <= right_border 
            && array[left_child] > array[max_index]) {
        max_index = left_child;
    }

    if(right_child <= right_border
            && array[right_child] > array[max_index] ) {
        max_index = right_child;
    }

    if(max_index != root_index) {
        
        /*swap*/
        array[max_index] = array[max_index] ^ array[root_index];
        array[root_index] = array[max_index] ^ array[root_index];
        array[max_index] = array[max_index] ^ array[root_index];

        /*don't forget to continue adjust heap*/
        build_max_heap(array, max_index, len);
    }
   
    //fprintf(stdout, "max_index=%d\n", max_index); 
    return;
}

void build_heap(int* array, int len) {
    if(array == NULL || len <= 0) {
        return;
    }

    int last_root = len/2-1;
    int left_border = 0x00;
    int i =0;
    for(i=last_root; i>=left_border; i--) {
        build_max_heap(array, i, len);
    }

    return;
}

void heap_sort(int* array, int len) {
    
    if(array == NULL || len <= 0) {
        return;
    }

    int right_border = len - 1;
    int left_border = 0x00;
    build_heap(array, len);
    int i = 0;
    for(i=0; i<len; i++) {

        array[left_border] = array[left_border] ^ array[right_border];
        array[right_border] = array[left_border] ^ array[right_border];
        array[left_border] = array[left_border] ^ array[right_border];
        right_border-=1;

        build_heap(array, right_border+1);
    }
}

int main() {

    #define LEN 10

    int test_array[LEN] = {3,2,1,6,5,4,9,8,7,0};
    
    build_heap(test_array, LEN);
    int i = 0 ;
    for(i=0; i<LEN; i++) {
        fprintf(stdout,"%d ",test_array[i]);
    }
    fprintf(stdout,"\n");

    heap_sort(test_array, LEN);
    for(i=0; i<LEN; i++) {
        fprintf(stdout,"%d ",test_array[i]);
    }
    fprintf(stdout,"\n");

    return 0;
}
