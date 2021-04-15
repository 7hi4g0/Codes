-module(day2).
-export([get/2, calculate_price/1, tic_tac_toe/1]).

get([], _) -> no_match;
get([{Key, Value}|_], Key) -> Value;
get([_|RestMap], Key) -> get(RestMap, Key).

calculate_price(Items) -> [{Product, Quantity * Price} || {Product, Quantity, Price} <- Items].

tic_tac_toe(Board) ->
    case Board of
        [X, _, _,
         X, _, _,
         X, _, _] -> X;
        [_, X, _,
         _, X, _,
         _, X, _] -> X;
        [_, _, X,
         _, _, X,
         _, _, X] -> X;
        [X, X, X,
         _, _, _,
         _, _, _] -> X;
        [_, _, _,
         X, X, X,
         _, _, _] -> X;
        [_, _, _,
         _, _, _,
         X, X, X] -> X;
        [X, _, _,
         _, X, _,
         _, _, X] -> X;
        [_, _, X,
         _, X, _,
         X, _, _] -> X;
        _ -> case lists:any(fun (X) -> X =:= n end, Board) of
                 true  -> no_winner;
                 false -> cat
             end
    end.
