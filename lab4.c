#include <fcntl.h> 
#include <stdio.h> 
#include <semaphore.h> 
#include <pthread.h> 


FILE *f; 
sem_t *semaphore1; 
sem_t *semaphore2; 

void* th1(void* args) { 
int i, sum1 = 0; 
for (i = 0; i < 20; i++) { 
sem_wait(semaphore2); 
f = fopen("txt.txt", "a"); 
sum1 += 2; 
fprintf(f, "Шаг %d суммы = %d \n", i, sum1); 
fclose(f); 
sem_post(semaphore1); 
} 
} 

void* th2(void* args) { 
int i, sum2 = 0; 
for (i = 0; i < 20; i++) { 
sem_wait(semaphore1); 
f = fopen("txt.txt", "a"); 
sum2 += 10; 
fprintf(f, "Шаг %d разности = %d \n", i, sum2); 
fclose(f); 
sem_post(semaphore2); 
} 
} 

int main() { 

f = fopen("txt.txt", "w"); 
pthread_t thread1; 
pthread_t thread2; 

semaphore1 = sem_open("/first_sem", O_CREAT, S_IWUSR, 0); 
semaphore2 = sem_open("/second_sem", O_CREAT, S_IWUSR, 1); 

pthread_create(&thread1, NULL, th1, NULL); 
pthread_create(&thread2, NULL, th2, NULL); 

pthread_join(thread1, NULL); 
pthread_join(thread2, NULL); 

sem_unlink("/first_sem"); 
sem_unlink("/second_sem"); 
return 0; 
}
