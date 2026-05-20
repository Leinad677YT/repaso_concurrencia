-module(notifier).

-export([start/0, register/1, send/2]).

-export([loop/1]).


%% API

start() -> spawn(?MODULE, loop, [[]]).

register(N) -> 
    N!{register,self()}.

send(N,Msg) -> 
    N!{notify,Msg}.

%% Internal functions

loop(RegisteredList) -> 
    receive
        {register,Pid} ->
            loop([Pid | [X || X <- RegisteredList, not (X == Pid)]]);
        {notify,Msg} ->
            [X!Msg || X <- RegisteredList],
            loop(RegisteredList);
        stop -> true
    end.

%% ejecutar para ver que todo funciona:

% N = notifier:start().
% notifier:register(N).
% notifier:register(N).
% notifier:send(N,test).
% receive test -> true end.
% receive test -> true end.

%% si tras el primer receive aparece `true` en la salida
%% y tras el segundo se queda esperando, todo funciona correctamente