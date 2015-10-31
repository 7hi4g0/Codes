# Needs fixing!
# ':' is not being properly replaced by 'atPutAttr'
OperatorTable addAssignOperator(":", "atPutAttr")

curlyBrackets := method(
	a := Map clone
	call message arguments foreach(arg,
		a doMessage(arg))
	a)

Map atPutAttr := method(
	self atPut(
		call evalArgAt(0) asMutable removePrefix("\"") removeSuffix("\""),
		call evalArgAt(1)))

Builder := Object clone
Builder indent := 0
Builder forward := method(
	arguments := call message arguments
	write("\t" repeated(indent), "<", call message name)
	if(arguments at(0) type == "Map",
		arguments at(0) foreach(attr, value,
			write(" \"", attr, "\"=\"", value, "\""))
		arguments removeFirst)
	writeln(">")
	self indent = indent + 1
	call message arguments foreach(
		arg,
		content := self doMessage(arg);
		if(content type == "Sequence",
			writeln("\t" repeated(indent), content)))
	self indent = indent - 1
	writeln("\t" repeated(indent), "</", call message name, ">"))

{"type": "main"} println
Builder ul(
	li({"type": "main"}, "Io"),
	li("Lua"),
	li("JavaScript"))
