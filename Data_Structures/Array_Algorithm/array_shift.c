#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void array_reverse(int* a, int left, int right) {
    
    if(a == NULL) {
        return;
    }
    
    int tmp = 0x00;
    while(left < right) {
        tmp = a[left];
        a[left] = a[right];
        a[right] = tmp;
        left++;
        right--;
    }

    return;
}

// 左移K位，数组长度为n
void shift_left_k(int* a, int n, int k) {
    
    if(a == NULL || n <= 0 || k < 0) {
        return;
    }

    k = k%n;

    array_reverse(a, 0, k-1);
    array_reverse(a, k, n-1);
    array_reverse(a, 0, n-1);
}

// 右移K位，数组长度为n
void shift_right_k(int* a, int n, int k) {
    
    if(a == NULL || n <= 0 || k < 0) {
        return;
    }

    k = k%n;

    array_reverse(a, 0, n-1);
    array_reverse(a, 0, k-1);
    array_reverse(a, k, n-1);
}

void show(int* a, int n) {
    if(a == NULL || n<=0) {
        return;
    }

    int i = 0x00;
    for(i=0x00; i<n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[10] = {1,2,3,4,5,6,7,8,9,0};
    int lena = sizeof(a)/sizeof(int);
    show(a,lena);
    shift_left_k(a, lena, 2);
    show(a,lena);

    int b[10] = {1,2,3,4,5,6,7,8,9,0};
    int lenb = sizeof(b)/sizeof(int);
    show(b,lenb);
    shift_right_k(b, lenb, 2);
    show(b,lenb);

    //printf("%d\n",sizeof(void));
    return 0;
}
