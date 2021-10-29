import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    var (n, m) = readln()
    val a = Array(n) { readln() }
    val ok = Array(n) { BooleanArray(m) {false} }
    val answer = ArrayList<Pair<Int, Int>>()
    for (i in 0 until n - 1)
        for (j in 0 until m - 1)
            if (a[i][j] + a[i + 1][j] + a[i][j + 1] + a[i + 1][j + 1] == 4) {
                ok[i][j] = true
                ok[i + 1][j] = true
                ok[i][j + 1] = true
                ok[i + 1][j + 1] = true
                answer.add(Pair(i + 1, j + 1))
            }

    for (i in 0 until n)
        for (j in 0 until m)
            if (a[i][j] == 1 && !ok[i][j])
                return writeln(-1)

    writeln(answer.size)
    writeln(answer.joinToString("\n") { it.first.toString() + " " + it.second.toString() })
}

private fun PrintWriter.readSolveWrite() {
    run()
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun writeln(vararg strings: Any) = println(strings.map{if (it is IntArray) it.joinToString(" ") else it}.joinToString(" "))

private fun readln() = getIntArray()

private fun getIntArray() = readLine()!!.splitToIntArray()

private fun bufferOut(block: PrintWriter.() -> Unit) = PrintWriter(System.out).use { block(it) }

fun main() = bufferOut { readSolveWrite() }

private fun String.splitToIntArray(): IntArray {
    val n = length
    if (n == 0) return IntArray(0) // EMPTY
    var res = IntArray(4)
    var m = 0
    var i = 0
    while (true) {
        var cur = 0
        var neg = false
        var c = get(i) // expecting number, IOOB if there is no number
        if (c == '-') {
            neg = true
            i++
            c = get(i) // expecting number, IOOB if there is no number
        }
        while (true) {
            val d = c.toInt() - '0'.toInt()
            require(d in 0..9) { "Unexpected character '$c' at $i" }
            require(cur >= Integer.MIN_VALUE / 10) { "Overflow at $i" }
            cur = cur * 10 - d
            require(cur <= 0) { "Overflow at $i" }
            i++
            if (i >= n) break
            c = get(i)
            if (c == ' ') break
        }
        if (m >= res.size) res = res.copyOf(res.size * 2)
        res[m++] = if (neg) cur else (-cur).also { require(it >= 0) { "Overflow at $i" } }
        if (i >= n) break
        i++
    }
    if (m < res.size) res = res.copyOf(m)
    return res
}// }}}
