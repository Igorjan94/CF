import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

const val M = 1000000

private fun run() {
    val (n) = readln()
    val s = readLine()!!.replace('(', '0').replace(')', '1')
    val a = readLine()!!
    val dp = Array(n) { IntArray(16) { M } }
    val states = listOf("0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111")
    val all = states.indices.toList()
    val restricted = listOf(3, 5)
    fun getDiff(s: String, t: String): Int {
        var c = 0
        for (i in s.indices)
            if (s[i] != t[i])
                ++c
        return c
    }
    for (j in states.indices) {
        val state = states[j].substring(1, 4)
        dp[0][j] = getDiff(state, s.substring(0, 3))
    }
    for (i in a.indices) {
        var curStates = all
        if (a[i] == '1')
            curStates = restricted
        for (j in all)
            if (dp[i][j] != M) {
                val prevState = states[j].substring(1, 4)
                for (k in curStates) {
                    val curState = states[k]
                    if (getDiff(prevState, curState) == 0) {
                        dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + ok(s[i + 3] != curState[3]))
                    }
                }
            }
    }
    var ans = M
    for (i in all)
        ans = min(ans, dp[n - 3][i])
    if (ans == M)
        writeln(-1)
    else
        writeln(ans)
}

private fun PrintWriter.readSolveWrite() {
    val (t) = readln()
    repeat(t) {
        run()
    }
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun writeln(vararg strings: Any) =
    println(strings.map { if (it is IntArray) it.joinToString(" ") else it }.joinToString(" "))

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
            @OptIn(kotlin.ExperimentalStdlibApi::class)
            val d = c.code - '0'.code
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
