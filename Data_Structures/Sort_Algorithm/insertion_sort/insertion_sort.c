#include "../include/common.h"

/***
 * 插入排序:
 * a[0] a[1] a[2] a[3] ... 已经从小到大排好序，直到a[n]
 * a[n]依次与a[n-1] a[n-1] a[n-3] ... 比较
 * 只要a[x]比a[n]大，就把这个值向后移动一个位置，以便挪出一个空位，用于放置a[n]的值
 * 直到a[y]比a[n]小，则a[n]的值应该放在a[y+1]的位置上
 * 需要临时变量来存储a[n]的值，因为a[n]本身可能会被覆盖
 * ***/
void insertion_sort(int* array, int len) {
    
    if(array == NULL || len == 0) {
        return;
    }

    int right_border = len - 1;
    int left_border = 0x00;
    int curr_border = 1;
    int tmp_val = 0x00;
    int i = 0x00;

    for(curr_border = left_border + 1; curr_border <= right_border; curr_border++) {
        tmp_val = array[curr_border]; //临时变量,用来存储当前要插入的值
        for(i=curr_border - 1; i >= left_border; i--) {
            //如果被比较的值比要插入的值大，
            //说明要插入的值应该在这个值之前，
            //则这个值需要向后移动，以便挪出一个空位
            if(tmp_val < array[i]) {
                array[i+1] = array[i];
            } else {
                break;//直到遇到比要插入的值小的值
            }
        }
        array[i+1] = tmp_val;//把要插入的值放在比它小的值的位置的后面
    }
    return;
}

int main() {
    #define LEN 10
    //int test_array[LEN] = {5,4,3,2,1,9,8,7,6,0};
    int test_array[LEN] = {2,1,3,5,4,6,8,9,7,0};
    int i = 0;
    insertion_sort(test_array, LEN);
    for( i = 0; i<LEN; i++) {
        fprintf(stdout,"%d ",test_array[i]);
    }
    fprintf(stdout,"\n");
    return 0;
}
