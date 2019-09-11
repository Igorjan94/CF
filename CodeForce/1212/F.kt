import java.io.*
import kotlin.math.*
import kotlin.collections.*

fun main() = bufferOut { readSolveWrite() }

private fun PrintWriter.readSolveWrite() {
    val n = readLine()!!.toLong()
    var degs = arrayListOf<Long>()
    degs.add(0L)
    degs.add(1L)
    for (i in 1..18)
        degs.add(degs[i] * 10L + 1L)

    fun rec(x: Long, d: Int): Long
    {
        val cur = abs(x)
        if (cur % degs[d] == 0L)
            return cur / degs[d] * d
        val k = cur / degs[d]
        val temp1 = (k * d + rec(cur - k * degs[d], d - 1))
        val temp2 = ((k + 1) * d + rec((k + 1) * degs[d] - cur, d - 1))
        return min(temp1, temp2)
    }
    println(rec(n, 18))
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun getIntArray() = readLine()!!.splitToIntArray()

private fun bufferOut(block: PrintWriter.() -> Unit) = PrintWriter(System.out).use { block(it) }

data class Pt(val x: Int, val y: Int, val i: Int, var ans: Int)

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
