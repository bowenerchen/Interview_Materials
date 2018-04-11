#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

// 在已从小到大排好序的数组中二分查找某个值
// 假设数组中没有重复的数字
// 时间复杂度logn
int binary_search(int* arr, int len, int val) {

    int left = 0x00;
    int right = len - 1;
    int mid = 0x00;

    while(left <= right) {
        mid = (left+right)/2;
        if(val > arr[mid]) { // 值在右边
            left = mid + 1;
        } else if(val < arr[mid]) {// 值在左边
            right = mid - 1;
        } else {// 值相等
            return mid;
        }
    }
return -1;
}


int main() {

    int a[10] = {0,1,2,3,4,5,6,7,8,9};

    int val = 11;
    int index = binary_search(a, sizeof(a), val);
    
    if(index != -1) {
        printf("val=%d,index=%d\n",val,index);
    } else {
        printf("val=%d not found\n",val);
    }

    return 0;

}
