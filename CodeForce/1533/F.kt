import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun binSearch(L: Int, R: Int, f: (Int) -> Boolean): Int {
    var l = L
    var r = R
    while (r - l > 1) {
        val m = l + (r - l) / 2
        if (f(m))
            l = m
        else
            r = m
    }
    return if (f(r)) r else l
}

private fun run() {
    val s = readLine()!!
    val n = s.length
    val ans = Array(n) { 0 }
    val p = Array(n + 1) { 0 }
    for (i in 0 until n)
        p[i + 1] = p[i] + ok(s[i] == '1')
    for (i in 0 until n) {
        var j = 0
        while (j < n) {
            ans[i]++
            j = binSearch(j, n) {
                val ones = p[it] - p[j]
                val zeros = it - j - ones
                ones <= i + 1 || zeros <= i + 1
            }
        }
    }
    writeln(ans.joinToString(" "))
}

private fun PrintWriter.readSolveWrite() {
//    val (t) = readln()
    for (q in 1..1) {
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
