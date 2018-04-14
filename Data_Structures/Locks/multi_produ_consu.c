#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>
#include<signal.h>

#define _SIZE_ 3 //缓冲区大小

#define PRODUCER 3
#define CONSUMER 3

#define EMPTY 0
#define FULL  1

int ringbuf[_SIZE_] = {0x00};

pthread_mutex_t lock_produce = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_consumer = PTHREAD_MUTEX_INITIALIZER;

sem_t producing; //生产者在空的情况下开始生产
sem_t consuming;  //消费者在满的情况下开始消费

static volatile int produce_index = 0x00;
static volatile int consume_index = 0x00;

static volatile int produce_sem_count = 0x00;
static volatile int consume_sem_count = 0x00;

static volatile int running = 0x01;

void* thread_pro(void* arg)
{
    printf("thread %lu producing now\n", pthread_self());
    sleep(1);

    while(running)
    {
        sem_wait(&producing);//如果可以生产了

        pthread_mutex_lock(&lock_produce); //加锁

        // 内部检验测试
        if(ringbuf[produce_index] == EMPTY) {
            ringbuf[produce_index] = FULL; //生产
            printf("thread %lu producing ringbuf[%d]\n", pthread_self(), produce_index);
        } else {
            printf("ERROR ringbuf[%d] = FULL can not be produced\n", produce_index);
        }

        produce_index++;
        if(produce_index == _SIZE_) { //如果已经满了

            produce_index = 0x00;
        }

        pthread_mutex_unlock(&lock_produce); //解锁
        sem_post(&consuming);//只要生产了就通知消费者可以消费了

        sleep(1);
    }
    pthread_exit(NULL);
}

void* thread_con(void* arg)
{
    printf("thread %lu consuming now\n", pthread_self());
    sleep(1);

    while(running)
    {
        sem_wait(&consuming);//如果可以消费了

        pthread_mutex_lock(&lock_consumer); //加锁
        
        //内部检验测试
        if(ringbuf[consume_index] == FULL) { //验证是否确实是被生产了
            ringbuf[consume_index] = EMPTY; //消费
            printf("thread %lu consuming ringbuf[%d]\n", pthread_self(), consume_index);
        } else {
            printf("ERROR ringbuf[%d] = EMPTY can not be consumed\n", consume_index);
        }

        consume_index++;

        if(consume_index == _SIZE_) { //如果消费完了

            consume_index = 0x00;
            //sem_post(&producing);//通知生产者
        }
        pthread_mutex_unlock(&lock_consumer); //解锁
        sem_post(&producing);//只要消费了就通知生产者可以生产了
        sleep(1);
    }

    pthread_exit(NULL);
}

void sig_handle(int sig) {
    
    if(sig == SIGINT) {

        running = 0x00;
        sleep(1);
        sem_destroy(&producing);
        printf("sem destroy &producing\n");

        sem_destroy(&consuming);
        printf("sem destroy &consuming\n");

        pthread_mutex_destroy(&lock_produce);
        printf("mutex destroy &lock_produce\n");

        pthread_mutex_destroy(&lock_consumer);
        printf("mutex destroy &lock_consumer\n");
    }
}

int main()
{

    signal(SIGINT, sig_handle);

    sem_init(&producing,0,_SIZE_); //初始一共有_SZIE_个数据可以被生产
    sem_init(&consuming,0,0);
    
    pthread_t pro_tid[PRODUCER] = {0x00};
    pthread_t con_tid[CONSUMER] = {0x00};

    for(int i = 0; i < PRODUCER; i++) {
        pthread_create(&pro_tid[i],NULL,thread_pro,NULL);
    }

    for(int i = 0; i < CONSUMER; i++) {
        pthread_create(&con_tid[i],NULL,thread_con,NULL);
    }

    for(int i = 0; i < PRODUCER; i++) {
        pthread_join(pro_tid[i],NULL);
        printf("join PRODUCER %lu\n", pro_tid[i]);
    }

    for(int i = 0; i < CONSUMER; i++) {
        pthread_join(con_tid[i],NULL);
        printf("join CONSUMER %lu\n", pro_tid[i]);
    }

    //sem_destroy(&producing);
    //sem_destroy(&consuming);
    //
    //pthread_mutex_destroy(&lock_produce);
    //pthread_mutex_destroy(&lock_consumer);
    
    return 0;
}
