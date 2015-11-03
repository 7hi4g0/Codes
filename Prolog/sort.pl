%
split([], [], []).
split([Head], [Head], []).
split(List, Left, Right) :-
	length(List, Total),
	Half is Total // 2,
	length(Right, Half),
	append(Left, Right, List).

merge([], Right, Right).
merge(Left, [], Left).
merge([HeadLeft|Left], [HeadRight|Right], [HeadLeft|List]) :-
	HeadLeft =< HeadRight,
	merge(Left, [HeadRight|Right], List).
merge([HeadLeft|Left], [HeadRight|Right], [HeadRight|List]) :-
	HeadLeft > HeadRight,
	merge([HeadLeft|Left], Right, List).

merge_sort([], []).
merge_sort([Head], [Head]).
merge_sort(List, SortedList) :-
	split(List, Left, Right),
	merge_sort(Left, SortedLeft),
	merge_sort(Right, SortedRight),
	merge(SortedLeft, SortedRight, SortedList).
