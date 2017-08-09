class Person(firstName: String) {
  println("Outer constructor")
  def this(firstName: String, lastName: String) {
    this(firstName)
    println("Inner constructor")
  }
  def talk() = println("Hi")
}

val thiago = new Person("Thiago")
val tandrade = new Person("Thiago", "Andrade")
