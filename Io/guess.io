magicNumber := Random value(1, 101) floor

in := File standardInput
previous := nil

10 repeat(
	"Guess the number between 1 and 100:" println
	guess := in readLine asNumber
	if(guess == magicNumber,
		break,
		if(previous == nil,
			"Wrong number, try again!" println,
			if(((previous - magicNumber) / (guess - magicNumber)) abs > 1,
				"Hotter" println,
				"Colder" println)))
	previous = guess)

if(guess == magicNumber,
	"You won!" println,
	"You failed to guess the number. Better luck next time!" println)
