#include <stdlib.h>
#include <pthread.h>

/**
 * El main() y demás lo hice yo aparte para
 * probar cómo iba haciendo, el ej no los pide
 */

#define CAR_AMOUNT 200

void enter_bridge(int direction){

}

void exit_bridge(int direction){
    
}


void* car(void* direction){


    enter_bridge(*(int*)direction);

    // crosses

    exit_bridge(*(int*)direction);


    return NULL;
}





int main(void){
    
    int dirs[2] = {0,1};
    pthread_t cars[CAR_AMOUNT];

    srand(time(NULL));


    for (int i = 0; i<CAR_AMOUNT; i++)
        pthread_create(&cars[i],NULL,car,&dirs[rand() % 2]);

    for (int i = 0; i < CAR_AMOUNT; i++)
        pthread_join(cars[i],NULL);
    
    return 0;
}