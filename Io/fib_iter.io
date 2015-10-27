fib := method(nth,
	previous := 0
	current := 1
	swap := 0
	for(i,2,nth,
		swap = current
		current = previous + current
		previous = swap)
	return current)

fib(1) println
fib(2) println
fib(3) println
fib(4) println
fib(5) println
fib(6) println
fib(7) println
fib(8) println
fib(9) println
fib(10) println
