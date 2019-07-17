import java.io.*// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun PrintWriter.readSolveWrite() {
    val (n) = readln()
    val a = readln()
    val (q) = readln()
    build(a, 0, 0, n - 1)
    for (i in 1..q) {
        val (l, r) = readln()
        writeln(get(l, r, n))
    }
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private val MAX_N = 500_000
private val t = IntArray(4 * MAX_N + 1)

private fun build(a: IntArray, p: Int, tl: Int, tr: Int): Int {
    val x = if (tl == tr) {
        a[tl]
    } else {
        val m = (tl + tr) / 2
        max(
            build(a, 2 * p + 1, tl, m),
            build(a,2 * p + 2, m + 1, tr)
        )
    }
    t[p] = x
    return x
}

private fun get0(p: Int, tl: Int, tr: Int, l: Int, r: Int): Int {
    if (l > r) return -1
    if (l == tl && r == tr) return t[p]
    val m = (tl + tr) / 2
    return max(
        get0(2 * p + 1, tl, m, l, min(r, m)),
        get0(2 * p + 2, m + 1, tr, max(l, m + 1), r)
    )
}

private fun get(l: Int, r: Int, n: Int): Int = get0(0, 0, n - 1, l, r)

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
