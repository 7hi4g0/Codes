val movies =
  <movies>
    <movie genre="action">Pirates of the Caribbean</movie>
    <movie genre="fairytale">Edward Scissorhands</movie>
  </movies>

val movieNodes = movies \ "movie"

println(movieNodes(0))
println(movieNodes(0) \ "@genre")
