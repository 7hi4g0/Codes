List myAverage := method(
	sum := 0
	self foreach(a,
		if(a type != "Number", Exception raise("Can only average Numbers"))
		sum = sum + a)
	sum / self size)

list(1, 2, 3) myAverage println
list() myAverage println
list(2, 2, 5) myAverage println
list(1, "hello", 3) myAverage println
