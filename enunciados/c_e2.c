#include <stdlib.h>
#include <pthread.h>

/**
 * El main() y demás lo hice yo aparte para
 * probar cómo iba haciendo, el ej no los pide
 */

#define GROUP_AMOUNT 40
#define VISITOR_AMOUNT 200

int visit() {return 1;}

struct group {
    /*const */int members; // total number of members in the group // NO const PARA LAS PRUEBAS
    pthread_mutex_t *counter_m; // Mutex to protect counter
    int counter; // members of this group that are currently inside the museum
};

int capacity;

void *visitor(void *arg) {
    struct group *grp = arg;

    // Access
    
    visit();
    
    // Exit

    return NULL;
}





int main(void){
    
    struct group groups[GROUP_AMOUNT] = {0};
    int visitor_groups[VISITOR_AMOUNT] = {0};
    pthread_t visitors[VISITOR_AMOUNT] = {0};

    srand(time(NULL));

    for (int i = 0; i< VISITOR_AMOUNT; i++) {
        int _group = rand() % GROUP_AMOUNT;

        visitor_groups[i] = _group;

        if (groups[_group].members == 0) {
            groups[_group].counter_m = malloc(sizeof(pthread_mutex_t));

            pthread_mutex_init(groups[_group].counter_m,NULL);
        }
        groups[_group].members++;
    }

    for (int i = 0; i < VISITOR_AMOUNT; i++)
        pthread_create(&visitors[i],NULL,visitor,&groups[visitor_groups[i]]);


    for (int i = 0; i < VISITOR_AMOUNT; i++)
        pthread_join(visitors[i],NULL);
    
    return EXIT_SUCCESS;
}