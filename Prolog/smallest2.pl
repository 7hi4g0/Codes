%
smaller(X, Y, X) :- (X =< Y).
smaller(X, Y, Y) :- (X > Y).
smallest([Head], Head).
smallest([Head|Tail], Smaller) :-
	smallest(Tail, TailSmaller), smaller(Head, TailSmaller, Smaller).
