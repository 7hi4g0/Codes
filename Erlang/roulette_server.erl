-module(roulette_server).
-behaviour(gen_server).

-export([start_link/0]).
-export([pull_trigger/1]).
-export([init/1, handle_call/3, handle_cast/2, handle_info/2]).

start_link() ->
    gen_server:start_link({local, gun}, roulette_server, [], []).

pull_trigger(Number) ->
    gen_server:call(gun, Number).

init(_Args) ->
    {ok, empty}.

handle_call(3, From, empty) ->
    gen_server:reply(From, bang),
    exit({roulette,die,at,erlang:time()});
handle_call(Number, _From, empty) when is_number(Number) ->
    {reply, click, empty}.

handle_cast(_, empty) ->
    {ok, empty}.

handle_info(Number, empty) when is_number(Number) ->
    case Number of
        3 -> io:format("bang~n"), exit({roulette,die,at,erlang:time()});
        _ -> io:format("click~n"), {noreply, empty}
    end.
