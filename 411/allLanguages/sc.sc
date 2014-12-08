object Main extends App {
  val line = readLine()
  if (line.matches(".{5,}") && line.matches(".*[a-z].*") && line.matches(".*[0-9].*") && line.matches(".*[A-Z].*"))
      println("Correct")
  else
      println("Too weak")
}
