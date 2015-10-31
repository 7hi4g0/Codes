Builder := Object clone
Builder indent := 0
Builder forward := method(
	writeln("\t" repeated(indent), "<", call message name, ">")
	self indent = indent + 1
	call message arguments foreach(
		arg,
		content := self doMessage(arg);
		if(content type == "Sequence",
			writeln("\t" repeated(indent), content)))
	self indent = indent - 1
	writeln("\t" repeated(indent), "</", call message name, ">"))

Builder ul(
	li("Io"),
	li("Lua"),
	li("JavaScript"))
