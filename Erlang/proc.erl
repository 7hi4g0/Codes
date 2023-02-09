-module(proc).
-export([init/0]).

init() ->
    process_flag(trap_exit, true),
    loop().

loop() ->
    receive
        ping -> io:format("pong~n");
        die -> exit({goodbye});
        {'EXIT', _From, _Reason} -> io:format("I'm dead~n")
    end,
    loop().
