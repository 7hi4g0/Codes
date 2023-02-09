-module(monitor_monitor).
-export([start/0]).

start() ->
    spawn(fun init/0).

init() ->
    process_flag(trap_exit, true),
    loop(empty).

register_proc(empty, Proc, Fun) ->
    link(Proc),
    {[{Proc, Fun}]};
register_proc({List}, Proc, Fun) ->
    link(Proc),
    {[{Proc, Fun} | List]}.

restart_if_found(empty, _Proc, _NewState) ->
    empty;
restart_if_found({[]}, _Proc, NewState) ->
    io:format("Process not registered~n"),
    NewState;
restart_if_found({[{Proc, Fun}|Rest]}, Proc, {NewList}) ->
    io:format("Restarting ~p~n", [Fun]),
    NewPid = apply(Fun, []),
    link(NewPid),
    {[{NewPid, Fun} | NewList] ++ Rest};
restart_if_found({[Head|Rest]}, Proc, {NewList}) ->
    restart_if_found({Rest}, Proc, {[Head | NewList]}).

loop(State) ->
    receive
        {register, Proc, Fun} ->
            io:format("Registering process ~p~n", [Proc]),
            NewState = register_proc(State, Proc, Fun),
            loop(NewState);
        {'EXIT', From, _Reason} ->
            NewState = restart_if_found(State, From, {[]}),
            loop(NewState)
    end.
