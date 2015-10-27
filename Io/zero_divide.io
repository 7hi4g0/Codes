old_divide := Number getSlot("/")
Number setSlot("/", method(quo,
	if(quo == 0,
		0,
		old_divide(quo))))

writeln("2 / 3 = " .. (2 /3))
writeln("7 / 0 = " .. (7 /0))
writeln("0 / 0 = " .. (0 /0))
writeln("0 / 5 = " .. (0 /5))
writeln("7 / 5 = " .. (7 /5))
writeln("3 / 5 = " .. (3 /5))
