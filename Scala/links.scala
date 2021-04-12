import scala.io._
import scala.actors._
import Actor._

object PageLoader {
  val linkRegex = "<a[^>]+href=\"([^\"]+)\"[^>]*>".r
  def getPage(url: String) = Source.fromURL(url)("ISO-8859-1").mkString
  def getPageSize(url: String) = getPage(url).length
  def getPageSizeAndLinks(url: String) = {
    val page = getPage(url)
    (page.length, linkRegex.findAllMatchIn(page).map(_.group(1)).toList)
  }
}

val urls = List("http://www.amazon.com/",
                "https://www.twitter.com/",
                "https://www.google.com/",
                "https://www.cnn.com/")

def getPageSizeConcurrently() = {
  val caller = self

  for (url <- urls) {
    actor { 
      val (size, links) = PageLoader.getPageSizeAndLinks(url)
      caller ! (url, size, links) 
    }
  }

  for (i <- 1 to urls.size) {
    receive {
      case (url: String, size: Int, links: List[_]) =>
        println(url + ": Size - " + size + ", Links - " + links.length)
    }
  }
}

getPageSizeConcurrently
