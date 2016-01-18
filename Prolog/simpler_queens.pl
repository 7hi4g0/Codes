%
diags1(Queens, Diagonals) :- diags1(Queens, Diagonals, 1).
diags1([], [], _).
diags1([Col|QueensTail], [Diagonal|DiagonalsTail], Row) :-
	Diagonal #= Col - Row + 8,
	diags1(QueensTail, DiagonalsTail, Row + 1).

diags2(Queens, Diagonals) :- diags2(Queens, Diagonals, 1).
diags2([], [], _).
diags2([Col|QueensTail], [Diagonal|DiagonalsTail], Row) :-
	Diagonal #= Col + Row,
	diags2(QueensTail, DiagonalsTail, Row + 1).

eight_queens(Board) :-
	length(Board, 8),
	fd_domain(Board, 1, 8),

	Cols = Board,
	diags1(Board, Diags1),
	diags2(Board, Diags2),

	fd_all_different(Cols),
	fd_all_different(Diags1),
	fd_all_different(Diags2),
	
	fd_labeling(Board).
