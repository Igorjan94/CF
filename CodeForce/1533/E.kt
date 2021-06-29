import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    val (n) = readln()
    val a = readln()
    val b = readln()
    a.sort()
    b.sort()
    val p = Array(n + 1) {-2000000000}
    for (i in 0 until n)
        p[i + 1] = max(p[i], b[i] - a[i])
    val s = Array(n + 1) {-2000000000}
    for (i in n - 1 downTo 0)
        s[i] = max(s[i + 1], b[i + 1] - a[i])
    //writeln(p.joinToString(" "))
    //writeln(s.joinToString(" "))
    val (m) = readln()
    val c = readln()
    val ans = IntArray(m) {0}
    for (q in 0 until m) {
        val x = c[q]
        var l = 0
        var r = n
        while (r - l > 1) {
            val M = l + (r - l) / 2
            if (a[M] <= x)
                l = M
            else
                r = M
        }
        var j = r
        if (a[l] > x)
            j = l
        ans[q] = max(p[j], s[j])
            //writeln(x, "->", j, a[j], p[j], s[j], b[j + 1])
        ans[q] = max(ans[q], b[j] - x)
    }
    writeln(ans)
}

private fun PrintWriter.readSolveWrite() {
//    val (t) = readln()
    for (q in 1..1) {
        run()
    }
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun writeln(vararg strings: Any) = println(strings.map{if (it is IntArray) it.joinToString(" ") else it}.joinToString(" "))

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
