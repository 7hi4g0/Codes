%
rev([], []).
rev([Head|Tail], Reverse) :-
	append(TailReverse, [Head], Reverse), rev(Tail, TailReverse). 
