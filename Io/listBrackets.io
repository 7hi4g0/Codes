// Naive way:
// Message arguments is a list already, no need to clone List and append
squareBrackets := method(
	l := List clone
	call message arguments foreach(arg,
		l append(doMessage(arg)))
	l)
squareBrackets := method(
	call message arguments)

["Hello", "List", 42] println
