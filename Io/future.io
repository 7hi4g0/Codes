futureResult := URL with("http://www.google.com.br") @fetch

writeln("This will block until the result gets back!")
writeln("Result is ", futureResult size, " bytes")
