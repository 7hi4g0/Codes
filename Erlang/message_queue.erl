-module(message_queue).
-export([init/0]).

init() ->
    loop().

consume() ->
    receive
        {msg, Number} -> io:format("~p~n", [Number]), consume()
    after 0 -> ok
    end.

loop() ->
    receive
        ping -> io:format("pong~n");
        process -> consume()
    end,
    loop().
