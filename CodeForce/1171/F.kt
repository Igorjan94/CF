import java.io.*
import kotlin.math.*
import kotlin.Triple
import kotlin.collections.*

fun main() = bufferOut { readSolveWrite() }

private fun PrintWriter.readSolveWrite() {
    val (t) = getIntArray()
    for (q in 1..t) {
        val (n) = getIntArray()
        var a = arrayListOf<Triple<Int, Int, Int>>()
        var ans = IntArray(n)
        for (i in 1..n) {
            ans[i - 1] = 2
            val (x, y) = getIntArray()
            a.add(Triple(x, y, i - 1))
        }
        a.sortWith(compareBy({it.first}, {it.second}, {it.third}))
        var i = 0
        var r = a[0].first
        while (i < n && a[i].first <= r) {
            ans[a[i].third] = 1
            r = max(r, a[i++].second)
        }
        if (i == n)
            println(-1)
        else
            println(ans.joinToString(" "))
    }
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun getIntArray() = readLine()!!.splitToIntArray()

private fun bufferOut(block: PrintWriter.() -> Unit) = PrintWriter(System.out).use { block(it) }

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
