import java.io.*
import kotlin.math.*
import kotlin.collections.*

private val MAX_N = 200_000
private val t = IntArray(MAX_N * 2 + 1)
 
private fun update(index: Int) {
    var i = index + MAX_N
    while (i < MAX_N * 2) {
        t[i]++
        i = i or (i + 1)
    }
}

private fun get(index: Int): Int {
    var i = index + MAX_N
    var res = 0
    while (i >= 0) {
        res += t[i]
        i = (i and (i + 1)) - 1
    }
    return res
}

fun main() = bufferOut { readSolveWrite() }

private fun PrintWriter.readSolveWrite() {
    fun writeln(vararg strings: Any) {
        println(strings.map{if (it is IntArray) it.joinToString(" ") else it}.joinToString(" "))
    }
    val (n, e) = getIntArray()
    val p = getIntArray()
    fun solve(e: Int): Long {
        t.fill(0, 0, MAX_N * 2)
        update(0)

        var ans = 0L
        var cur = 0
        for (i in 0 .. n - 1) {
            if (p[i] <= e)
                cur--
            else
                cur++
            ans += get(-cur)
            update(-cur)
        }
        return ans
    }
    writeln(solve(e) - solve(e - 1))
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
