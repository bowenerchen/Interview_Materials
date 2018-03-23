#include "../include/common.h"

#define LEN 10
int test_array[LEN]={4,3,2,1,9,8,7,6,5,0};

/***
 * 选择排序：每一次遍历，把最大的值放在数组的最右边
 * 时间复杂度O(n^2)
 * 因为需要不断的遍历数组，每次遍历的边界向左边移动一位
 * ***/
void selection_sort(int* array, int len) {

    if(array == NULL || len == 0) {
        fprintf(stderr, "invalid parameter\n");
        return ;
    }

    int left_border  = 0x00;
    int right_border = len - 1;
    int tmp_max = 0x00;
    int tmp_max_index = 0x00;
    int i = 0, j = 0;
    
    for(right_border = len - 1; right_border > left_border; right_border--) {

        /*假设最大值是最左边的值*/
        tmp_max = array[ right_border ];
        tmp_max_index = right_border;

        for(i=left_border; i<right_border; i++) {
            if( tmp_max < array[i] ) {
                tmp_max = array[i]; //当前遍历过程中，不断更新当前的最大值
                tmp_max_index = i;
            }
        }
        
        /*使用异或方式来交换的时候，需要考虑到最大值与最开始的边界一致的情况*/
        if(tmp_max_index ^ right_border) {
            /*交换最右边的值和找到的最大值*/
            array[right_border]  = array[right_border] ^ array[tmp_max_index];
            array[tmp_max_index] = array[right_border] ^ array[tmp_max_index];
            array[right_border]  = array[right_border] ^ array[tmp_max_index];
        }
    }
}

int main() {

    int i = 0;
    for(i=0; i<LEN; i++) {
        fprintf(stdout, "%d ", test_array[i]);
    }
    fprintf(stdout,"\n");

    selection_sort(test_array, LEN);

    for(i=0; i<LEN; i++) {
        fprintf(stdout, "%d ", test_array[i]);
    }
    fprintf(stdout,"\n");
}
