#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

/***
 *  编写一个程序，开启3个线程，这3个线程的ID分别为Ａ、Ｂ、Ｃ，每个线程将自己的ID在屏幕上打印10遍，要求输出结果必须按ABC的顺序显示；如：ABCABC...依次递推
 * ***/

/***
 * 线程C加锁
 * 线程C判断flag_c进入cond_waiti解锁，阻塞并等待cond_b_to_c
 * 
 * 线程B加锁
 * 线程B判断flag_b进入cond_wait解锁，阻塞并等待cond_a_to_b
 * 
 * 线程A加锁
 * 线程A判断flag_a
 * 线程A打印
 * 线程A置flag_b
 * 线程A发送信号通知线程B
 * 线程A进入cond_wait解锁，阻塞并等待cond_c_to_a
 *
 * 线程B从cond_wait唤醒并加锁
 * 线程B判断flag_b
 * 线程B打印
 * 线程B置flag_c
 * 线程B发信号通知线程C
 * 线程B进入cond_wait解锁并等待cond_a_to_b
 *
 * 线程C从cond_wait唤醒并加锁
 * 线程C判断flag_c
 * 线程C打印
 * 线程C发送信号通知线程A
 * 线程C进入cond_wait解锁并等待cond_b_to_c
 *
 * 线程A从cond_wait唤醒并加锁
 * 线程A解锁
 * 
 * ***/
#define COUNT 3
static pthread_t tid_a, tid_b, tid_c;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t cond_a_to_b = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_b_to_c = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond_c_to_a = PTHREAD_COND_INITIALIZER;

static int flag_a = 0x01;
static int flag_b = 0x00;
static int flag_c = 0x00;

void* thread_c(void* arg) {
    int count = 0x00;
    while(1) {
        pthread_mutex_lock(&mutex);
        while(flag_c != 0x01) {
            pthread_cond_wait(&cond_b_to_c, &mutex);
        }
        printf("thread_c\n");
        sleep(1);
        flag_c = 0x00;
        flag_a = 0x01;
        pthread_cond_signal(&cond_c_to_a);
        pthread_cond_wait(&cond_b_to_c, &mutex);
        pthread_mutex_unlock(&mutex);

        count++;
        if(count == COUNT) {
            pthread_exit(NULL);
        }
    }
}

void* thread_b(void* arg) {
    int count = 0x00;
    while(1) {
        pthread_mutex_lock(&mutex);
        while(flag_b != 0x01) {
            pthread_cond_wait(&cond_a_to_b, &mutex);
        }
        printf("thread_b\n");
        sleep(1);
        flag_b = 0x00;
        flag_c = 0x01;
        pthread_cond_signal(&cond_b_to_c);
        pthread_cond_wait(&cond_a_to_b, &mutex);
        pthread_mutex_unlock(&mutex);

        count++;
        if(count == COUNT) {
            pthread_exit(NULL);
        }
    }
}

void* thread_a(void* arg) {
    int count = 0x00;
    while(1) {
        pthread_mutex_lock(&mutex);
        while(flag_a != 0x01) {
            pthread_cond_wait(&cond_c_to_a, &mutex);
        }
        printf("thread_a\n");
        sleep(1);
        flag_a = 0x00;
        flag_b = 0x01;
        pthread_cond_signal(&cond_a_to_b);
        pthread_cond_wait(&cond_c_to_a, &mutex);
        pthread_mutex_unlock(&mutex);

        count++;
        if(count == COUNT) {
            pthread_exit(NULL);
        }
    }
}

int main() {

    pthread_create(&tid_c, NULL, thread_c, NULL);
    pthread_create(&tid_b, NULL, thread_b, NULL);
    pthread_create(&tid_a, NULL, thread_a, NULL);

    //pthread_join(tid_a , NULL);
    //pthread_join(tid_b , NULL);
    //pthread_join(tid_c , NULL);

    pthread_detach(tid_a);
    pthread_detach(tid_b);
    pthread_detach(tid_c);

    while(1) {
        sleep(1);
    }
return 0;
}
