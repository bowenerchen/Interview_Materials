#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int count = 0x00;
void reverse_int(int n, int* arr) {
    if(arr == NULL) {
        return;
    }

    count++;
    if(n > 10) {
        reverse_int(n/10, arr+1); // 按指针步长加1
    }

    *arr = n%10;
}

int main() {

    int arr[100] = {0x00};

    int n = 12345;

    reverse_int(n, arr);
    
    for( int i = 0x00; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

return 0;
    
}
