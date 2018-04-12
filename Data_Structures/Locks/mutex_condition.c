#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>

/***
1）有一int型全局变量g_flag初始值为0；
2）在主线称中起动线程1，打印“this is thread1”，并将g_Flag设置为1
3）在主线称中启动线程2，打印“this is thread2”，并将g_Flag设置为2
4）线程序1需要在线程2退出后才能退出
5）主线程在检测到g_flag从1变为2，或者从2变为1的时候退出
 * ***/

static int g_flag = 0x00;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread_1(void* arg) {

    printf("this is thread1\n");

    pthread_mutex_lock(&mutex);
    if(g_flag == 2) {
        pthread_cond_signal(&cond);
    }

    g_flag = 1;

    pthread_mutex_unlock(&mutex);

    pthread_join(*(pthread_t*)arg, NULL);

    printf("leave thread1\n");
    return NULL;
}

void* thread_2(void* arg) {

    printf("this is thread2");

    pthread_mutex_lock(&mutex);
    if(g_flag == 1) {
        pthread_cond_signal(&cond);
    }

    g_flag = 1;

    pthread_mutex_unlock(&mutex);

    pthread_join(*(pthread_t*)arg, NULL);

    printf("leave thread2\n");
    return NULL;
}

int main() {

    pthread_t tid1 = 0x00;
    pthread_t tid2 = 0x00;
    int res = 0x00;
    
    res = pthread_create(&tid1, NULL, thread_1, &tid2);
    if(res != 0) {
        printf("error thread_1\n");
    }

    res = pthread_create(&tid2, NULL, thread_2, &tid1);
    if(res != 0) {
        printf("error thread_2\n");
    }

    pthread_cond_wait(&cond, &mutex);

    pthread_cond_destroy(&cond);

    pthread_mutex_destroy(&mutex);
    printf("leave main\n");

return 0;
}
