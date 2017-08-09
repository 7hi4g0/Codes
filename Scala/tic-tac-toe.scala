def whoWon(game:List[Char]):Char = {
  assert(game.length == 9)
  assert(game.forall((c) => c == 'X' || c == 'O' || c == ' '))
  if (game(0) != ' ' && game(0) == game(1) && game(1) == game(2)) {
    game(0)
  }
  else if (game(3) != ' ' && game(3) == game(4) && game(4) == game(5)) {
    game(3)
  }
  else if (game(6) != ' ' && game(6) == game(7) && game(7) == game(8)) {
    game(6)
  }
  else if (game(0) != ' ' && game(0) == game(3) && game(3) == game(6)) {
    game(0)
  }
  else if (game(1) != ' ' && game(1) == game(5) && game(4) == game(7)) {
    game(1)
  }
  else if (game(2) != ' ' && game(2) == game(5) && game(5) == game(8)) {
    game(2)
  }
  else if (game(0) != ' ' && game(0) == game(4) && game(4) == game(8)) {
    game(0)
  }
  else if (game(2) != ' ' && game(2) == game(4) && game(4) == game(6)) {
    game(2)
  }
  else if (game.exists((c) => c == ' ')) {
    ' '
  }
  else {
    'T'
  }
}
println(whoWon(List('X','X','X','O',' ','O','O',' ',' ')))
println(whoWon(List('X','O','X','X','O','O','O','X','X')))
println(whoWon(List('X','O','X','X','O','O','O','X',' ')))
println(whoWon(List('X','O','X','X','O','O','O','T',' ')))
