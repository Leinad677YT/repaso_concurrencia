# Ejercicios

## Concurrencia

### Erlang 1. Notificador

Implemente en Erlang un servicio de propagación de mensajes. El API de este servicio tiene tres funciones:

- `notifier:start()`, que arranca un servicio de propagación y devuelve su PID.
- `notifier:register(N)`, que registra al proceso que la llama en el notificador `N`
- `notifier:send(N,Msg)`, que envía el mensaje `Msg` a todos los procesos registrados en el notificador `N`.

```erl
-module(notifier).

-export([start/0, register/1, send/2]).
-export([loop/...]).

%% API

start() -> spawn(?MODULE,loop, []).

register(N) -> ...
send(N,Msg) -> ...

%% Internal functions

loop() ->
...
```

Implemente las funciones `send/2`, `register/1` y `loop`. Puede añadir parámetros a `loop` si lo necesita.
