Red [
	Title: "Function definition test"
	Author: "Thiago Dourado de Andrade"
	File: "function.red"
]

test: func [
	/cool
		num [integer!]
][
	print "Working \o/"
	if cool [
		print num
	]
]

test
test/cool 9
