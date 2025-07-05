#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define MAX 1024

char *buffer;
sem_t empty, full, mutex;

void *producer(void *arg) {
    while (1) {
        sem_wait(&empty);  // 等待空位
        sem_wait(&mutex);  // 进入临界区

        printf("Producer: Enter product: ");
        fgets(buffer, MAX, stdin);  // 生产产品到缓冲区

        sem_post(&mutex);  // 离开临界区
        sem_post(&full);   // 标记缓冲区已满
    }
    return NULL;
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);   // 等待产品
        sem_wait(&mutex);  // 进入临界区

        printf("Consumer: Read product: %s", buffer);
        memset(buffer, 0, MAX);  // 清空缓冲区

        sem_post(&mutex);  // 离开临界区
        sem_post(&empty);  // 标记缓冲区为空
    }
    return NULL;
}

int main() {
    buffer = (char *)malloc(MAX * sizeof(char));
    sem_init(&empty, 0, 1);  // 初始空位为1
    sem_init(&full, 0, 0);    // 初始产品为0
    sem_init(&mutex, 0, 1);   // 互斥锁初始可用

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    free(buffer);

    return 0;  // ctrl+c 退出程序
}