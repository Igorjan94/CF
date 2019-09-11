import java.io.*
import kotlin.math.*
import kotlin.collections.*

fun main() = bufferOut { readSolveWrite() }

private fun PrintWriter.readSolveWrite() {
    val n = readLine()!!.toInt()
    val a = getLongArray()
    for (i in 0..n-1) {
        val m = a.toMutableSet()
        val b = a.copyOf(n)
        var j = 0
        var curr = a[i]
        while (m.size > 0) {
            b[j++] = curr
            m.remove(curr)
            if (m.contains(curr * 2L))
                curr *= 2L
            else if (curr % 3L == 0L && m.contains(curr / 3L))
                curr /= 3L
            else break;
        }
        if (j == n)
            println(b.joinToString(" "))
    }
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun getLongArray() = readLine()!!.splitToLongArray()

private fun bufferOut(block: PrintWriter.() -> Unit) = PrintWriter(System.out).use { block(it) }

data class Pt(val x: Long, val y: Long, val i: Long, var ans: Long)

private fun String.splitToLongArray(): LongArray {
    val n = length
    if (n == 0) return LongArray(0) // EMPTY
    var res = LongArray(4)
    var m = 0
    var i = 0
    while (true) {
        var cur = 0L
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
            require(cur >= Long.MIN_VALUE / 10) { "Overflow at $i" }
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
