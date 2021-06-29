import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    var (n) = readln()
    n = n * 2 - 2
    val s = Array(n) {readLine()!!}.mapIndexed{ i, it ->  Pair(it, i) }.sortedBy { it.first.length }
    val ans = CharArray(n)
    ans[s[n - 2].second] = 'P'
    ans[s[n - 1].second] = 'S'
    fun check(ans: CharArray): Boolean {
        for (i in n - 3 downTo 0 step 2) {
            val prefix = s[if (ans[s[i + 1].second] == 'P') i + 1 else i + 2].first
            val suffix = s[if (ans[s[i + 1].second] == 'S') i + 1 else i + 2].first

            if (prefix.startsWith(s[i].first) and suffix.endsWith(s[i - 1].first)) {
                ans[s[i].second] = 'P'
                ans[s[i - 1].second] = 'S'
            } else if (prefix.startsWith(s[i - 1].first) and suffix.endsWith(s[i].first)) {
                ans[s[i].second] = 'S'
                ans[s[i - 1].second] = 'P'
            } else return false
        }
        return true
    }
    if (!check(ans)) {
        ans[s[n - 2].second] = 'S'
        ans[s[n - 1].second] = 'P'
        if (!check(ans))
            writeln("ASSERT")
    }
    writeln(ans.joinToString(""))

}

private fun PrintWriter.readSolveWrite() {
    //val (t) = readln()
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
