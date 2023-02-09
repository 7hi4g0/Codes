-module(translate_service_monitor).
-export([start/0]).

start() ->
    Pid = spawn(fun init/0),
    Pid ! new,
    Pid.

init() ->
    process_flag(trap_exit, true),
    loop().

loop() ->
    receive
        new ->
            io:format("Starting new translate service.~n"),
            register(translate, spawn_link(translate_service, loop, [])),
            loop();
        {'EXIT', From, Reason} ->
            io:format("service ~p killed because of ~p.~n", [From, Reason]),
            self() ! new,
            loop();
        Any ->
            io:format("Unknown message.~n~p~n", [Any]),
            loop()
    end.


