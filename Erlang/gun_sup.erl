-module(gun_sup).
-behaviour(supervisor).

-export([start_link/0]).
-export([init/1]).

start_link() ->
    supervisor:start_link(gun_sup, []).

init(_Args) ->
    ChildrenSpec = [#{id => gun,
                      start => {roulette_server, start_link, []}}],
    {ok, {#{}, ChildrenSpec}}.
