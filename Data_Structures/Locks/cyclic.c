
/***
 *子线程循环 1 次，接着主线程循环 1 次，接着又回到子线程循环 1 次，接着再回到主线程又循环 1 次，如此循环5次，试写出代码。
 * ***/


/***
 *  主线程加锁
 *  主线程判断flag不符合,进入cond_wait 解锁并阻塞
 *
 *  子线程加锁
 *  子线程判断flag_1符合
 *  子线程工作并置flag
 *  子线程发出信号唤醒主线程
 *  子线程进入cond_wait解锁并阻塞
 *
 *  主线程从cond_wait被唤醒并加锁
 *  主线程工作并置flag_1
 *  主线程发出信号唤醒子线程
 *  主线程解锁
 *
 *  子线程从cond_wait被唤醒并加锁
 *  子线程解锁
 * ***/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

#define COUNT 2
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int flag = 0x00;
static int flag_1 = 0x01;

void* thread_1(void* arg) {
    
    pthread_detach(pthread_self());
    int count = 0x00;
    while(1) {

        pthread_mutex_lock(&mutex);
        printf("thread_1 get mutex lock\n");

        while(flag_1 != 0x01) {
            pthread_cond_wait(&cond, &mutex);
        }        

        printf("thread_1 working...\n");
        sleep(1);

        flag = 0x01;
        flag_1 = 0x00;
        printf("thread_1 set flag = 0x01\n");

        pthread_cond_signal(&cond);
        printf("thread_1 send cond signal\n");

        printf("thread_1 cond wait\n");
        pthread_cond_wait(&cond, &mutex);

        printf("thread_1 set mutex unlock\n");
        pthread_mutex_unlock(&mutex);
        
        count++;
        if(count == COUNT) {
            pthread_exit(NULL);
        }
    }
}

int main() {

    pthread_t tid = 0x00;
    pthread_create(&tid, NULL, thread_1, NULL);

    int count = 0x00;
    while(1) {
        pthread_mutex_lock(&mutex);
        printf("main thread get mutex lock\n");

        while( flag != 0x01) {
            printf("main thread cond wait\n");
            pthread_cond_wait(&cond, &mutex);
        }

        flag = 0x00;
        flag_1 = 0x01;
        printf("main thread set flag = 0x00\n");

        printf("main thread working...\n");
        sleep(1);
        
        pthread_cond_signal(&cond);
        printf("main thread send cond signal\n");

        pthread_mutex_unlock(&mutex);
        printf("main thread set mutex unlock\n");

        count++;
        if(count == COUNT) {
            exit(0);
        }
    }
}
