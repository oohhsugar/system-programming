define _CRT_SECURE_NO_WARNINGS
#define _CRT_RAND_S
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>


sem_t semaphore1;
sem_t semaphore2;
 
static int counter = 0;
  
void* worker1(void* args) {
	 int i;
    int local;
    for (i = 0; i < 10; i++) {
        sem_wait(&semaphore1);
        local = counter;
        printf("worker1 - %d\n", local);
        local++;
        counter = local;
        Sleep(10);
        sem_post(&semaphore2);
    }
}
 
void* worker2(void* args) {
    int i;
    int local;
    for (i = 0; i < 10; i++) {
        sem_wait(&semaphore2);
        local = counter;
        printf("worker 2 - %d\n", local);
        local--;
        counter = local;
        Sleep(10);
        sem_post(&semaphore1);
}
 
void main() {
    pthread_t thread1;
    pthread_t thread2;
  
 
    sem_open(&semaphore1, 0, 0);
    sem_open(&semaphore2, 0, 0);
     
    pthread_create(&thread1, NULL, worker1, NULL);
    pthread_create(&thread2, NULL, worker2, NULL);

 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
 
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    wait();
}
