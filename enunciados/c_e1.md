# Ejercicios

## Concurrencia

### 1. Puente Estrecho

Un puente antiguo de ancho reducido solo permite el tráfico simultáneo de vehículos en
un sentido. Se desea diseñar un sistema que controle el acceso al puente de forma que un
vehículo espere a la entrada si hay vehículos cruzando en sentido opuesto.
Cada vehículo está representado por un thread que ejecuta la función `car`, y recibe como
parámetro la dirección en la que cruza (`0` o `1`).

```c
void enter_bridge(int direction){
    ...
}

void exit_bridge(int direction){
    ...
}


void* car(void* direction){


    enter_bridge(*(int*)direction);

    // Crosses the bridge

    exit_bridge(*(int*)direction);


    return NULL;
}

```

- a) Implemente las funciones `enter_bridge` y `exit_bridge` de tal forma que se cumplan las restricciones especificadas. Puede modificar la función `car` o añadir parámetros a `enter_bridge` y `exit_bridge` si lo considera necesario.
- b) El puente tiene un límite máximo de peso que solo pérmite `MAX_CARS` simultaneos. Modifique `enter_bridge` y `exit_bridge` para respetar esta limitación.
- c) Implemente el ejercicio anterior con semáforos, usando el contador interno para limitar el número de vehículos en el puente.