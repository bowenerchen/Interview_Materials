#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void prim(int m, int n) {
    if(m<=n) { //跳出递归的条件
        return;
    }
    while( m%n != 0) n++;
    m = m/n;
    printf("%d ", n);
    prim(m,n);
return;
}

int main() {
    //int m = 435234;
    
    prim(13142 , 2);

return 0;
}
