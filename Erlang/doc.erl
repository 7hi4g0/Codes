-module(doc).
-export([loop/0]).

loop() ->
    process_flag(trap_exit, true),
    receive
        {die, Reason} ->
            exit(Reason);
        {'EXIT', From, Reason} ->
            io:format("~p: ~p~nI died!~n", [From, Reason])
    end,
    loop().
