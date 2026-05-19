#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

/**
 * El main() y demás lo hice yo aparte para
 * probar cómo iba haciendo, el ej no los pide
 */

#define GROUP_AMOUNT 12
#define VISITOR_AMOUNT 1000

int visit() {
    return EXIT_SUCCESS;
}

struct group {
    /*const */int members; // total number of members in the group // NO const PARA LAS PRUEBAS
    pthread_mutex_t *counter_m; // Mutex to protect counter
    int counter; // members of this group that are currently inside the museum

    pthread_cond_t *notifier; // condition to enter the museum
};

pthread_mutex_t used_m;
pthread_cond_t used_c;

int used = 0;
int capacity = 400;

void *visitor(void *arg) {
    struct group *grp = arg;

    pthread_mutex_lock(grp->counter_m);
        // si primero de grupo, mira si va a caber completo
        if (grp->counter == 0) {
            printf("<!> (%4d) - %p\n",grp->members,grp->counter_m);fflush(stdout);
            pthread_mutex_lock(&used_m);
                // espera por espacio suficiente
                while(grp->members + used > capacity){
                    pthread_cond_wait(&used_c, &used_m);
                }

                used+= grp->members;
                printf("-E- (%4d) - %p\n",grp->members,grp->counter_m);fflush(stdout);

            pthread_mutex_unlock(&used_m);
        }

        // una vez asegurado, entra
        grp->counter++;
        if (grp->counter == grp->members) {
            pthread_cond_broadcast(grp->notifier);
            printf("[L] (%4d) - %p\n",grp->members,grp->counter_m);fflush(stdout);
        }
        // solo van a levantarse 1 vez y no hay "ruido" por lo que no hay while
        else pthread_cond_wait(grp->notifier,grp->counter_m);
        
    pthread_mutex_unlock(grp->counter_m);

    // Access
    
    visit();
    
    // Exit

    pthread_mutex_lock(grp->counter_m);
        grp->counter--;
        if (grp->counter == 0){
            pthread_mutex_lock(&used_m);

                // libera espacio y avisa al resto de grupos
                used-=grp->members;
                pthread_cond_broadcast(&used_c);

            pthread_mutex_unlock(&used_m);
        }
    pthread_mutex_unlock(grp->counter_m);

    return NULL;
}





int main(void){
    
    struct group groups[GROUP_AMOUNT] = {0};
    int visitor_groups[VISITOR_AMOUNT] = {0};
    pthread_t visitors[VISITOR_AMOUNT] = {0};

    srand(time(NULL));

    pthread_mutex_init(&used_m,NULL);
    pthread_cond_init(&used_c,NULL);

    for (int i = 0; i< VISITOR_AMOUNT; i++) {
        int _group = rand() % GROUP_AMOUNT;

        visitor_groups[i] = _group;

        if (groups[_group].members == 0) {
            groups[_group].counter_m = malloc(sizeof(pthread_mutex_t));
            groups[_group].notifier = malloc(sizeof(pthread_cond_t));

            pthread_mutex_init(groups[_group].counter_m,NULL);
            pthread_cond_init(groups[_group].notifier,NULL);
        }
        groups[_group].members++;
    }

    for (int i = 0; i < VISITOR_AMOUNT; i++)
        pthread_create(&visitors[i],NULL,visitor,&groups[visitor_groups[i]]);


    for (int i = 0; i < VISITOR_AMOUNT; i++)
        pthread_join(visitors[i],NULL);
    
    return EXIT_SUCCESS;
}