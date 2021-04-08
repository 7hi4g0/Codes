import scala.io.Source
import scala.collection.mutable.HashMap

trait Censor {
  val curses: HashMap[String, String] = HashMap("shoot" -> "pucky", "darn" -> "beans")

  def censor(text: String): String = curses.foldLeft(text)({(text, replacement) => text.replace(replacement._1, replacement._2)})
}

object Censor extends Censor {
  def load(): Unit = {
    Source.fromFile("curses.txt").getLines()
      .map(_.split(","))
      .foreach({words => curses += words(0) -> words(1)})
  }
}

Censor.load()

println(Censor.censor("The shoot brown fox jumps over the darn dawg"))
