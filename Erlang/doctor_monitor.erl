-module(doctor_monitor).
-export([start/0]).

start() ->
    spawn(fun init/0).

init() ->
    process_flag(trap_exit, true),
    loop({no_proc, []}).

new_doctor() ->
    Pid = spawn_link(doctor, loop, []),
    Pid ! new,
    io:format("New doctor: ~p~n", [Pid]),
    Pid.

loop(State) ->
    {Pid, MonitorList} = State,
    receive
        new ->
            case Pid of
                no_proc -> 
                    io:format("Creating new doctor~n"),
                    NewPid = new_doctor();
                _Else ->
                    io:format("Cheking doctor~n"),
                    NewPid = case is_process_alive(Pid) of
                                 true -> Pid;
                                 false ->
                                     io:format("Recreating doctor~n"),
                                     new_doctor()
                             end
            end,
            loop({NewPid, MonitorList});
        {register, Proc, Fun} ->
            loop({Pid, [{Proc, Fun} | MonitorList]});
        status ->
            io:format("Doctor is running: ~p~n", [is_process_alive(Pid)]),
            loop(State);
        {'EXIT', From, Reason} when From =:= Pid ->
            io:format("Doctor died because of ~p~n", [Reason]),
            loop({new_doctor(), MonitorList});
        {'EXIT', From, Reason} ->
            case lists:keyfind(From, 1, MonitorList) of
                {_, Fun} ->
            io:format("Doctor died because of ~p~n", [Reason]),
            loop({new_doctor(), MonitorList});
        Msg ->
            io:format("Ignoring message: ~p~n", [Msg]),
            loop(State)
    end.

