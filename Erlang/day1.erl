-module(day1).
-export([count_words/1, count_to_ten/0, print_response/1]).

count_words([]) -> 0;
count_words([$\s|Rest]) -> count_words(Rest);
count_words([_|[]]) -> 1;
count_words([_,$\s|Rest]) -> 1 + count_words(Rest);
count_words([_|Rest]) -> count_words(Rest).

count_to_ten() -> count_up_to(1, 10).

count_up_to(N, N) -> io:fwrite("~p~n", [N]);
count_up_to(N, Max) -> io:fwrite("~p~n", [N]), count_up_to(N+1, Max).

print_response(success) -> io:fwrite("success~n");
print_response({error, Message}) -> io:fwrite("error: ~s~n", [Message]).
