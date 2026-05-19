#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define FUTURES_AMOUNT 30

struct future {
    void *(*f)(void*);
    void *arg;

    void* result;
    pthread_t thr;
};
struct future *promise(void *(*f)(void *), void *arg)
{
    struct future *future = malloc(sizeof(struct future));
    if (!future)
        return NULL;

    future->f = f;
    future->arg = arg;
    future->result = NULL;

    pthread_create(&future->thr,NULL,f,arg);

    return future;
}
void *force(struct future *future)
{
    assert(future);
 
    pthread_join(future->thr,future->result);

    future->result = future->f(future->arg);
    return future->result;
}
void free_future(struct future *future)
{
    assert(future);
    free(future);
}





struct result {
    int value1;
    char value2;
    unsigned long int potato;
};

void* function(void * arg){
    int displacement = *(int*)arg;
    struct result* res = malloc(sizeof(struct result));

        nanosleep(&(struct timespec){1+rand() % 1,0},NULL);

        res->value1 = 3 + displacement;
        res->value2 = '\\' + displacement;
        res->potato = - displacement;

    return (void*) res;
}

int main(){

    int aux[FUTURES_AMOUNT];
    struct future* futures[FUTURES_AMOUNT];

    srand(time(NULL));

    for (int i = 0; i < FUTURES_AMOUNT; i++) {
        aux[i] = rand() % (1<<(sizeof(char) * 8 -1));
        futures[i] = promise(function,&aux[i]);
    }

    for (int i = 0; i < FUTURES_AMOUNT; i++) {
        struct result* res = force(futures[i]);
        assert(res->value1 == (int)(3 + aux[i]));
        assert(res->value2 == (char)('\\' + aux[i]));
        assert(res->potato == (unsigned long int)(-aux[i]));
    }

    for (int i = 0; i < FUTURES_AMOUNT; i++) {
        free_future(futures[i]);
    }
    

    return EXIT_SUCCESS;
}