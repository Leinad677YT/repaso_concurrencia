-module(store).

-export([start/0, store/2, get/2]).

-export([loop/2]).

%% API

start() -> spawn(?MODULE, loop, [[],0]).

store(S, P) -> 
    S!{store,P}.

get(S, F) ->
    S!{get,F,self()},
    receive
        {error,Code} -> {error,Code};
        {ok,Product} -> {ok,Product}
    end.


%% Internal Functions


get_first([]) -> 
    {error,'no-product'};
get_first([E]) -> 
    {ok,E};
get_first([E | _]) -> 
    {ok,E}.


loop(ProductList, ProductId) ->
    receive
        {store,P} ->
            loop([{P,ProductId} | ProductList],ProductId+1);
        {get,F, Pid} ->
            self()!get_first([{Pi,Ii} || {Pi,Ii} <- ProductList ,F(Pi)]),
            receive
                {error,_} -> 
                    Pid!{error,'no-product'},
                    loop(ProductList,ProductId);
                {ok,{Prod,Id}} -> 
                    Pid!{ok,Prod},
                    loop([{Pi,Ii} || {Pi,Ii} <- ProductList, not (Ii == Id)],ProductId)
            end;
        stop -> true
    end.


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