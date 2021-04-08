val list = List("The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog")

println(list.foldLeft(0)({(sum, word) => sum + word.size}))
