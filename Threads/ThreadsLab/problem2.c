#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int i = 0;
pthread_mutex_t m;
void *thread(void * arg){
    int j;
    for(j = 0; j <= 10000; j++){
        pthread_mutex_lock(&m);
        i = i+1;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(int argc, char** argv){
    pthread_t t[1000];
    int j;
    pthread_mutex_init(&m, NULL);
    for(j = 0; j < 1000; j++){
        pthread_create(&t[j], NULL, thread, NULL);
    }
    for(j = 0; j < 1000; j++){
        pthread_join(t[j], NULL); 
    }
    printf("i=%d\n", i);
    pthread_mutex_destroy(&m);
    return 0;
    
}