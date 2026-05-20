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


%% ejecutar para ver que todo funciona:

% Fun = fun(X) -> true end.
% S = store:start().
% store:store(S,potato).
% store:store(S,tomato).
% store:store(S,potato).
% store:get(S,Fun).
% store:get(S,Fun).
% store:get(S,Fun).
% store:get(S,Fun).

%% si todo funciona correctamente, no debería haber excepciones y los
%% gets deberían recuperar 2x`potato`, 1x`tomato` y un error `'no-product'`