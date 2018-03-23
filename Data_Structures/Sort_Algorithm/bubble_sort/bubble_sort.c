#include "../include/common.h"

void bubble_sort(int* array, int len) {
    if(array == NULL || len == 0) {
        return;
    }

    int right_border = len - 1;
    int left_border = 0x00;
    int curr_border = 0x00;
    int i = 0x00;
    
    for(curr_border = right_border; curr_border > left_border; curr_border--) {
        for(i = 0; i < curr_border; i++) {
            if(array[i] > array[i+1]) {
                array[i] = array[i] ^ array[i+1];
                array[i+1] = array[i] ^ array[i+1];
                array[i] = array[i] ^ array[i+1];
            }
        }
    }
}

int main() {

    #define LEN 10
    //int test_array[LEN] = {2,1,3,5,4,6,8,7,9,0};
    int test_array[LEN] = {9,1,8,2,7,3,6,4,5,0};
    int  i = 0;
    bubble_sort(test_array, LEN);
    for(i=0;i<LEN;i++){
        fprintf(stdout, "%d ", test_array[i]);
    }
    fprintf(stdout, "\n");
    return 0;
}
