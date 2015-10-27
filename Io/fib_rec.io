fib := method(nth,
	if(nth == 1,
		1,
		if(nth == 2,
			1,
			fib(nth - 1) + fib(nth - 2))))

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
