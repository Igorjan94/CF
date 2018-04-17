import java.util.*

val random = Random()
fun rand(from: Int, to: Int) : Int {
    return random.nextInt(to - from) + from
}

fun main(args: Array<String>) {
    val s = Scanner(System.`in`)
    val ans = mutableListOf<Int>()
    with(s) {
        val n = nextInt()
        for (i in 1 .. n) {
            if (n <= 30) {
                ans.add(1 shl i)
            } else {
                ans.add(rand(0, 1000000000))
            }
        }
        println(ans.joinToString(separator = " "))
    }
}
