#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
void* myThread1(void* arg){
    int i =0;
    while(i < 10){
        
    printf("Hello from thread %d\n", i);
i++;
sleep(1);
}
    return NULL;
}

void* myThread2(void* arg){
    int i= 0;
        while(i < 10){
    printf("Hello from thread %d\n", i);
    i++;
    sleep(1);
}
    return NULL;
}


int main(){
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, myThread1, NULL);
    pthread_create(&t2, NULL, myThread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}