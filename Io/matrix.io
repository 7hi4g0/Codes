Matrix := List clone
Matrix dim := method(x, y,
	self preallocateToSize(y)
	for(elem, 1, y,
		self push(list() setSize(x)))
	return self)
Matrix set := method(x, y, value,
	self at(y) atPut(x, value)
	return self)
Matrix get := method(x, y,
	self at(y) at(x))
Matrix transpose := method(
	tm := Matrix clone
	cols := self size
	rows := self at(0) size
	tm dim(cols, rows)
	for(row, 0, rows - 1,
		for(col, 0, cols - 1,
			tm set(col, row, self get(row, col)))))
Matrix save := method(filename,
	f := File with(filename) truncateToSize(0) openForUpdating
	self foreach(col,
		f write(col join(", ") .. "\n"))
	f close)
Matrix load := method(filename,
	m := Matrix clone
	m = doString(File with(filename) openForReading contents))

m := Matrix clone dim(3, 3)
m set(0, 2, 3)
m set(2, 0, 7)
m get(2, 0) println
m get(2, 2) println

m save("matrix.txt")
