#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

enum status {
    invalid = 0,
    overflow
};

int error;

int my_atoi(char* str) {
    
    // 判断指针是否为空
    if(str == NULL) {
        error = invalid;
        return -1;
    }

    // 去除空格
    while(*str == ' ') {
        str++;
    }

    // 判断正负号
    int flag = 1;
    if(*str == '-') {
        flag = -1;
        str++;
    } else if(*str == '+') {
        str++;
    }

    int number = 0x00;
    while(*str != '\0' && *str != '\n') {
        if(*str <= '9' && *str >= '0'){
            
            number = number * 10 + (*str - '0');
            // 判断溢出
            if(number < 0) {
                if(flag == 1) { // 超过最大INT
                    printf("溢出，超过最大的int\n");
                    error = overflow;
                    //这里正确的应该return INT_MAX
                    return -1;
                } else if(flag == -1) {
                    printf("溢出，超过最小负数\n");
                    error = overflow;
                    //这里正确的应该return INT_MIN
                    return -1;
                }
            }           

        } else {
            // 如果有非法字符串
            error = invalid;
            return -1;
        }
        str++;
    }

return number * flag;
}

int main() {
    char* str = "-123456789999999";
    int number = my_atoi(str);
    printf("number=%d\n", number);

return 0;
}
