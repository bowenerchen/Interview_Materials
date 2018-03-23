#include "../include/common.h"

void quick_sort(int* array, int left_border, int right_border) {

    if(array == NULL || (left_border >= right_border)) {
        return;
    }

    int low = left_border;
    int high = right_border;
    int flag = array[low];

    while(low < high) {

        while(low < high && array[high] > flag) {
            high--;
        }

        while(low < high && array[low] < flag) {
            low++;
        }

        array[low] = array[low] ^ array[high];
        array[high] = array[low] ^ array[high];
        array[low] = array[low] ^ array[high];
    }

    array[low] = flag;

    quick_sort(array, left_border, low);
    quick_sort(array, low+1, right_border);
}

int main() {

    #define LEN  10
    //int test_array[LEN] = {3,1,2,6,5,4,9,8,7,0};
    int test_array[LEN] = {9,8,7,6,5,4,3,2,1,0};
    int i = 0;
    quick_sort(test_array, 0, LEN-1);
    for(i=0; i<LEN; i++) {
        fprintf(stdout, "%d ", test_array[i]);
    }
    fprintf(stdout, "\n");
    return 0;
}
