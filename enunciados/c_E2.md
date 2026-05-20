# Ejercicios

## Concurrencia

### Erlang 2. Almacén de Productos

Se desea implementar un almacén donde se puedan guardar y recuperar productos. El API es el siguiente:

- `store:start()`, que arranca un almacén y devuelve su PID.
- `store:store(S, P)`, que guarda el producto `P` en el almacén con pid `S`.
- `store:get(S, F)`, donde `S` es un almacén, y `F` un predicado sobre productos. La función devuelve `{error, no-product}` si no hay ningún producto que cumpla `F` en el almacén, y `{ok, P}` (siendo `P` un producto que cumple `F(P)`) si lo hay. Al devolver un producto se elimina del almacén.

```erl
-module(store).

-export([start/0, store/2, get/2]).

-export([loop/0]).

%% API

start() -> spawn(?MODULE, loop, []).

store(S, P) -> ...

get(S, F) -> ...

%% Internal Functions

loop() ->
...
```

Implemente las funciones `store/2`, `get/2` y `loop`. Puede añadir funciones auxiliares y parámetros a `loop` si lo necesita.
