#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

const char* my_strstr(const char* sub, const char* dest) {
    if(sub == NULL) {
        return dest;
    }

    if(dest == NULL) {
        return NULL;
    }

    const char* psub = sub;
    const char* pdest = dest;
    const char* start = dest;
    while(*pdest) {
        if(*psub == *pdest) {
            start = pdest;
            while(*pdest && *psub && (*psub == *pdest)) {
                printf("*psub=%c *pdest=%c\n", *psub, *pdest);
                psub++;
                pdest++;
            }
            if(*psub == '\0') {
                return start;
            } else {
                return NULL;
            }
        }
        pdest++;
    }
return NULL;
}

int main() {
    const char* dest = "12345";
    const char* sub = "23";

    if(my_strstr(sub, dest)) {
        printf("str %s is substr of %s\n", sub, dest);
    } else {
        printf("str %s is not substr of %s\n", sub, dest);
    }
return 0;
}
