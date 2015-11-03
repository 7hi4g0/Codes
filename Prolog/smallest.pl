%
smallest([Head], Head).
smallest([Head|Tail], Head) :-
	smaller(Tail, TailSmaller), Head =< TailSmaller.
smallest([Head|Tail], Smaller) :-
	smaller(Tail, Smaller), Head > Smaller.
