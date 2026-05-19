#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

/**
 * El main() y demás lo hice yo aparte para
 * probar cómo iba haciendo, el ej no los pide
 */

#define CAR_AMOUNT 40
#define MAX_CARS 3


enum dir {
    right = 0,
    left = 1,
    none
};

#define other(dir) ((dir==right) ? left : right)



static struct _bridge {
    int direction;
    int crossing;
    pthread_mutex_t status_mutex;
    pthread_cond_t wait_queue;
} bridge = {
    none,0, {0,0},
    {0}
};



void enter_bridge(int direction){
    
    pthread_mutex_lock(&bridge.status_mutex);

        // espera mientras alguien cuza y no es de tu sentido
        // O BIEN el puente está lleno
        while(bridge.direction == other(direction) || bridge.crossing == MAX_CARS) {
            pthread_cond_wait(&bridge.wait_queue,&bridge.status_mutex);
        }

        // empieza a cruzar
        bridge.crossing++;
        bridge.direction = direction;

    pthread_mutex_unlock(&bridge.status_mutex);
}

void exit_bridge(int direction){
    
    pthread_mutex_lock(&bridge.status_mutex);
    
        // sale del puente
        bridge.crossing--;

        // si no queda nadie cruzando, deja libre para los del otro sentido
        if (bridge.crossing == 0) {
            bridge.direction = none;
            printf(" - \n");fflush(stdout);
            pthread_cond_broadcast(&bridge.wait_queue);
        }
        // si se hizo hueco, despierta a los que esperan
        else if (bridge.crossing == MAX_CARS-1) { 
            pthread_cond_broadcast(&bridge.wait_queue);
        }
        
    pthread_mutex_unlock(&bridge.status_mutex);    
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

    pthread_mutex_init(&bridge.status_mutex,NULL);
    pthread_cond_init(&bridge.wait_queue,NULL);

    srand(time(NULL));


    for (int i = 0; i<CAR_AMOUNT; i++)
        pthread_create(&cars[i],NULL,car,&dirs[rand() % 2]);

    for (int i = 0; i < CAR_AMOUNT; i++)
        pthread_join(cars[i],NULL);
    
    return EXIT_SUCCESS;
}