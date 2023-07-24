#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int a;
    int b;

}pthread_arg;

typedef struct{
    int sum;
    int product;

}pthread_ret;

void* thread(void* arg){
    pthread_arg a = *(pthread_arg*) arg;
    printf("%d %d: I am alive!!(I think)\n", a.a, a.b);
    pthread_ret *b = malloc(sizeof(pthread_ret));
    b->sum = a.a + a.b;
    b->product = a.a * a.b;
    free(arg);
    return (void*) b;

}

int main(int argc, char** argv){
    int n = atoi(argv[1]);
    pthread_t *t;
    pthread_ret **r;
    t = malloc(n * sizeof(pthread_t));
    r = malloc(n * sizeof(pthread_ret *));
    int i;
    for(i = 0; i < n; i++){
        pthread_arg *arg = malloc(sizeof(pthread_arg));
        arg->a = i;
        arg->b = 2 * i - 1;
        pthread_create(&t[i], NULL, thread, (void*)arg);
    }
    for(i = 0; i < n; i++){
        pthread_join(t[i], (void *)&r[i]);
    }
    for(i = 0; i < n; i++){
        printf("thread %d returned: sum: %d, product: %d\n", i, r[i]->sum, r[i]->product);
        free(r[i]);
    }
    free(r);
    free(t);
    return 0;
}