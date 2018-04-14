#include<time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pthread.h>

static sem_t sema;
static sem_t semb;

void* thread_a(void* arg) {
    int count = 0x00;
    while(1) {
        sem_wait(&sema);//获取信号量并减一
        printf("thread_a doing work...\n");
        sleep(1);
        sem_post(&semb);//释放信号量并加一

        count++;
        if(count == 5) {
            pthread_exit(NULL);
        }
    }
}

void* thread_b(void* arg) {
    int count = 0x00;
    while(1) {
        sem_wait(&semb);//获取信号量并减一
        printf("thread_b doing work...\n");
        sleep(1);
        sem_post(&sema);//释放信号量并加一

        count++;
        if(count == 5) {
            pthread_exit(NULL);
        }
    }
}

int main() {
    pthread_t tida, tidb;

    sem_init(&sema, 0, 1); //信号量a激活
    sem_init(&semb, 0, 0); //信号量b未激活

    pthread_create(&tida, NULL, thread_a, NULL);
    pthread_create(&tidb, NULL, thread_b, NULL);

    pthread_join(tida, NULL);
    pthread_join(tidb, NULL);
    //pthread_detach(tida);
    //pthread_detach(tidb);

    sem_destroy(&sema);
    sem_destroy(&semb);

return 0;
}
