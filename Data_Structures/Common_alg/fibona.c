#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

long long fibonacci(unsigned n) {
    int result[2] = {0,1};
    if(n<2)
        return result[n];

    long long minusone = 1;
    long long minustwo = 0;
    long long fibn = 0;

    for(unsigned int i = 2; i <= n; i++) {
        fibn = minusone + minustwo;
        minustwo = minusone;
        minusone = fibn;
    }
    
    printf("fibonacci(%d)=%llu\n", n, fibn);
    return fibn;
}

int main() {

    fibonacci(10);

return 0;
}
