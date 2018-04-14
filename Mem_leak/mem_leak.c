#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
    int *a = (int*)malloc(sizeof(int));
    *a = 1;
    //free(a);
return 0;
}
