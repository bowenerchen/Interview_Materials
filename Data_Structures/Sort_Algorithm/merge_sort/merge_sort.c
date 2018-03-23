#include "../include/common.h"


void merge_sorted_array(int* array, int first, int mid, int last, int* tmp) {
    int left_border = first;
    int right_border = last;
    int mid_left = mid;
    int mid_right = mid+1;
    int index = 0;

    /*合并两个有序的数组，直到其中一个数组全部合并完*/
    while(left_border <= mid_left 
            && mid_right <= right_border) {
        if(array[left_border] <= array[mid_right]) {
            tmp[index++] = array[left_border++];
        } else {
            tmp[index++] = array[mid_right++];
        }
    }

    /*将剩下的元素全部拷贝到tmp里面*/
    while(left_border <= mid_left) {
        tmp[index++] = array[left_border++];
    }

    while(mid_right <= right_border) {
        tmp[index++] = array[mid_right++];
    }

    /*将tmp中已经合并完成的数组还原到array中*/
    int i = 0;
    for(i=0; i<index; i++){
        array[first+i] = tmp[i];
    }

    return;
}

void divided_to_sorted(int* array, int first, int last, int* tmp) {

    if(first < last) {
        int mid = (first + last)/2;
        divided_to_sorted(array, first, mid, tmp); //左边有序
        divided_to_sorted(array, mid+1, last, tmp); //右边有序
        merge_sorted_array(array, first, mid, last, tmp); //将两边的合并到一个数组里面
    }
}

void merge_sort(int* array, int len) {
    if(array == NULL || len <= 0) {
        return;
    }

    int left_border = 0;
    int right_border = len - 1;
    int* tmp = (int*)malloc(sizeof(int) * len);
    divided_to_sorted(array, left_border, right_border, tmp);

    free(tmp);
}

int main() {
    #define LEN 10
    int test_array[LEN] = {0};
    int i = 0;
    for(i=0; i<LEN; i++) {
        test_array[i] = rand()%LEN;
    }

    merge_sort(test_array, LEN);

    for(i = 0; i < LEN; i++) {
        fprintf(stdout, "%d ", test_array[i]);
    }
    fprintf(stdout, "\n");

    return 0;
}
