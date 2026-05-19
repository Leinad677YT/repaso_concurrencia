#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

/**
 * El main() y demás lo hice yo aparte para
 * probar cómo iba haciendo, el ej no los pide
 */

#define CAR_AMOUNT 40
#define MAX_CARS 2


enum dir {
    right = 0,
    left = 1,
    none
};

#define other(dir) ((dir==right) ? left : right)



static struct _bridge {
    int direction;
    int crossing[2];
    sem_t status_mutex;
    sem_t crossing_queue;
    sem_t wait_queue[2];
    
} bridge = {
    none,{0,0},
    {0},{0},{{0},{0}}
};



void enter_bridge(int direction){

    // bloquea contador de direccion
    sem_wait(&bridge.wait_queue[direction]);

    // aumenta, si fue el primero entonces espera por puente 
    // y el resto del sentido espera tras el
    bridge.crossing[direction]++;
    if (bridge.crossing[direction] == 1) {
        sem_wait(&bridge.status_mutex);
    }

    // permite seguir a su sentido
    sem_post(&bridge.wait_queue[direction]);

    // espera por limite de carga
    sem_wait(&bridge.crossing_queue);
}

void exit_bridge(int direction){
    
    // libera puesto en puente
    sem_post(&bridge.crossing_queue);

    sem_wait(&bridge.wait_queue[direction]);

    bridge.crossing[direction]--;

    if (bridge.crossing[direction] == 0) {
        printf(" - \n");fflush(stdout);
        sem_post(&bridge.status_mutex);
    }

    sem_post(&bridge.wait_queue[direction]);
}


void* car(void* direction){

    nanosleep(&(struct timespec){rand()%4,0},NULL);


    enter_bridge(*(int*)direction);

    // Crosses the bridge
        printf("%s\n",(*(int*)direction == right) ? "right" : "left");
        nanosleep(&(struct timespec){1,0},NULL);

    exit_bridge(*(int*)direction);


    return NULL;
}





int main(void){
    
    int dirs[2] = {left,right};
    pthread_t cars[CAR_AMOUNT];

    // "mutex" para contadores
    sem_init(&bridge.wait_queue[0],0,1);
    sem_init(&bridge.wait_queue[1],0,1);

    // "mutex" para direccion
    sem_init(&bridge.status_mutex,0,1);

    // semaforo de peso maximo
    sem_init(&bridge.crossing_queue,0,MAX_CARS);

    srand(time(NULL));


    for (int i = 0; i<CAR_AMOUNT; i++)
        pthread_create(&cars[i],NULL,car,&dirs[rand() % 2]);

    for (int i = 0; i < CAR_AMOUNT; i++)
        pthread_join(cars[i],NULL);
    
    return EXIT_SUCCESS;
}