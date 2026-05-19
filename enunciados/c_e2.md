# Ejercicios

## Concurrencia

### 2. Acceso de Grupos a un Museo

Se quiere diseñar un sistema para controlar la entrada de grupos a un museo con capacidad limitada (`capacity`). Los grupos tienen que gestionar la entrada de forma conjunta. Todos los miembros tienen que entrar al mismo tiempo, es decir, si no hay capacidad para todos deberían esperar hasta que se liberen plazas suficientes.  
Cada miembro del grupo ejecuta la función `visitor`, y recibe como parámetro una estructura `group` con información compartida por todos los miembros del mismo grupo.  
Añada el código necesario para gestionar la entrada salida de grupos a la función `visitor`.

```c
struct group {
    const int members; // total number of members in the group
    pthread_mutex_t *counter_m; // Mutex to protect counter
    int counter; // members of this group that are currently inside the museum
};

int capacity;

void *visitor(void *arg) {
    struct group *grp = arg;

    // Access
    
    visit();
    
    // Exit
}
```