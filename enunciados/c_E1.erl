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


%% ejecutar para ver que todo funciona:

% N = notifier:start().
% notifier:register(N).
% notifier:register(N).
% notifier:send(N,test).
% receive test -> true end.
% receive test -> true end.

%% si tras el primer receive aparece `true` en la salida
%% y tras el segundo se queda esperando, todo funciona correctamente