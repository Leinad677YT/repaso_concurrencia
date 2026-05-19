# Ejercicios

## Concurrencia

### 3. Futures

Una future es una abstracción para retrasar computaciones. Imaginemos que queremos calcular `c = f(a)` pero que `c` no lo usamos hasta mucho más adelante en el programa. Podemos transformar esto como `future = promise (f, a)` y en el uso de `c` como `force(future)`. Se da una implementación de referencia de `promise` y `force`. Puede asumirse que:

- Las funciones que vamos a usar toman un argumento void * y devuelven un valor del mismo tipo.
-  Se pueden hacer varios force para cada future. Existe una operacion free_future para liberar la future.

Implementar `future` para que cree un thread para realizar la operación y `force` para que si el thread ya ha terminado devuelva el valor calculado y en caso contrario espere a que el thread termine. La función `free_future` libera la memoria usada por la future. Pueden añadirse todos los campos que se consideren necesarios a la struct future.

Ejemplo de uso:

```c
struct arg {
    int i;
    int result;
}
void *add_one(void *v)
{
    struct arg *arg = v;
    arg->result = arg->i + 1;
    return NULL;
}
int main(void)
{
    struct arg a;
    struct future *future;
    a.i = 5;future = promise(add_one, &a);
    force(future);
    printf("The result is %d\n", a.result);
    free_future(future);
    return 0;
}
```

Implemente futures a partir del siguiente esqueleto:
```c
struct future {
    void *(*f)(void*);
    void *arg;
    ...
};
struct future *promise(void *(*f)(void *), void *arg)
{
    struct future *future = malloc(sizeof(struct future));
    if (!future)
    return NULL;
    future->f = f;
    future->arg = arg;
    return future;
}
void *force(struct future *future)
{
    assert(future);
    future->result = future->f(future->arg);
    return future->result;
}
void free_future(struct future *future)
{
    assert(future);
    free(future);
}
```