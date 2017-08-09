def rubyStyleLoop {
  println("for loop using Ruby-style iteration")
  args.foreach { arg =>
    println(arg)
  }
}

rubyStyleLoop
