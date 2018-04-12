#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int count_1(int n) {
    int count = 0x00;
    while(n) {
        count++;
        n=(n-1)&n;
    }
    return count;
}

int main() {
    int n = 4;
    printf("Total %d 1(s) in number %d\n", count_1(n), n);

    if(n&(n-1)) {
        printf("数字%d不是2的幂\n", n);
    } else {
        printf("数字%d是2的幂\n", n);
    }
    return 0;
}
