import java.io.*// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun PrintWriter.readSolveWrite() {
    val (n, m) = readln()
    var a = readln()
    var c = IntArray(n + 1) { 0 }
    for (i in 0..n - 1)
        c[i + 1] = c[i] + a[i]

    fun binSearch(ll: Int, rr: Int, v: Int): Int {
        var l = ll
        var r = rr
        while (r - l > 1) {
            val m = (l + r) / 2
            if (c[m] - c[ll] <= v)
                l = m
            else
                r = m
        }
        if (c[r] - c[ll] <= v)
            return r
        else
            return l
    }

    val (q) = readln()
    repeat(q) {
        var b = readln()
        b[0] = 0
        b += m + 1
        var j = 0
        for (i in 1..b.size - 1) {
            var d = b[i] - b[i - 1] - 1
            val next = binSearch(j, n, d)
            if (c[next] - c[j] > 0 && c[next] <= c[j] + d)
                j = next
        }
        if (j == n)
            writeln("YES")
        else
            writeln("NO")
    }
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun writeln(vararg params: Any) = println(params.joinToString(" "))

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
