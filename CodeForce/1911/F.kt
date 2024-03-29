import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    val N = 150000
    val (n) = readln()
    val a = readln()
    val dp = IntArray(N + 10) {0}
    val added = IntArray(N + 10) {0}
    for (x in a)
        ++dp[x]

    fun add(x: Int, step: Int): Boolean {
        if (dp[x] == 0) return false
        if ((added[x + step] == 0) and (dp[x + step] == 0) and (step == -1)) {
            dp[x]--
            added[x + step]++
            return true
        }
        if ((added[x + step] == 0) and (step == 1)) {
            dp[x]--
            added[x + step]++
            return true
        }
        return false
    }
    if ((dp[1] >= 2))
        add(1, +1)
    for (i in 2..N) {
        add(i, -1)
        if (dp[i] + added[i] >= 2)
            add(i, +1)
    }

    var ans = 0
    for (i in 1..N + 2)
        if ((dp[i] != 0) or (added[i] != 0))
            ++ans
    writeln(ans)
}

private fun PrintWriter.readSolveWrite() {
    for (q in 1..1) {
        run()
    }
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun writeln(vararg strings: Any) = println(strings.map{if (it is IntArray) it.joinToString(" ") else it}.joinToString(" "))

private fun readln() = getIntArray()

private fun getIntArray() = readLine()!!.splitToIntArray()

private fun bufferOut(block: PrintWriter.() -> Unit) = PrintWriter(System.out).use { block(it) }

data class Pt(val x: Int, val y: Int, val i: Int, var ans: Int)

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
