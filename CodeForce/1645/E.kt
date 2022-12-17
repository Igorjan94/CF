import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    val (n, k) = readln()
    var c = n.countOneBits()
    if (c > k) {
        writeln("NO")
        return
    }
    val a = IntArray(31) {0}
    for (i in 0..30)
        if (((1 shl i) and n) != 0)
            ++a[i]
    for (i in 30 downTo 1)
        if ((a[i] != 0) and (c < k)) {
            val diff = min(k - c, a[i])
            a[i] -= diff
            a[i - 1] += diff * 2
            c += diff
        }
    if (c < k) {
        writeln("NO")
        return
    }
    val ans = ArrayList<String>()
    for (i in 0..30)
        if (a[i] > 0)
            ans.add(IntArray(a[i]) {1 shl i}.joinToString(" "))
    writeln("YES")
    writeln(ans.joinToString(" "))
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
