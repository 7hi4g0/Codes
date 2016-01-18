%
splitN([], [], _).
splitN(List, [Left|Rows], N) :-
	length(Left, N),
	append(Left, Right, List),
	splitN(Right, Rows, N).
split9(List, Lists) :- splitN(List, Lists, 9).
split3(List, Lists) :- splitN(List, Lists, 3).

different(Lists) :-
	maplist(fd_all_different, Lists).

head_tail([Head|Tail], Head, Tail).

transpose([], []).
transpose([[]|_], []).
transpose(Rows, [Col|ColsTail]) :-
	maplist(head_tail, Rows, Col, RowsTails),
	transpose(RowsTails, ColsTail).

concat([],[]).
concat([Head|ListsTail], Concat) :-
	append(Head, ConcatsTail, Concat),
	concat(ListsTail, ConcatsTail).

blocks(Rows, Blocks) :-
	maplist(split3, Rows, Splited),
	transpose(Splited, LargeCols),
	concat(LargeCols, BlockCols),
	split3(BlockCols, BlockSplited),
	maplist(concat, BlockSplited, Blocks).

sudoku(Puzzle, Solution) :-
	Solution = Puzzle,
	sudoku(Solution).

sudoku(Puzzle) :-
	length(Puzzle, 81),
	
	fd_domain(Puzzle, 1, 9),

	split9(Puzzle, Rows), different(Rows),
	transpose(Rows, Cols), different(Cols),
	blocks(Rows, Blocks), different(Blocks),

	fd_labeling(Puzzle).

sudoku_solution(Puzzle) :-
	sudoku(Puzzle),
	format('\
~d ~d ~d | ~d ~d ~d | ~d ~d ~d~n\
~d ~d ~d | ~d ~d ~d | ~d ~d ~d~n\
~d ~d ~d | ~d ~d ~d | ~d ~d ~d~n\
------|-------|------~n\
~d ~d ~d | ~d ~d ~d | ~d ~d ~d~n\
~d ~d ~d | ~d ~d ~d | ~d ~d ~d~n\
~d ~d ~d | ~d ~d ~d | ~d ~d ~d~n\
------|-------|------~n\
~d ~d ~d | ~d ~d ~d | ~d ~d ~d~n\
~d ~d ~d | ~d ~d ~d | ~d ~d ~d~n\
~d ~d ~d | ~d ~d ~d | ~d ~d ~d~n', Puzzle).

