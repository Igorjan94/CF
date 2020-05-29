import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}
 
fun IntArray.longSum(): Long {
    var sum = 0L
    forEach { sum += it }
    return sum
}

private fun run() {
    val (n, m, q) = readln()
    var a = Array(n){ readln() }
    var total = a.map{ it.longSum() }.sum()
    var r = LongArray(n) {0L}
    var c = LongArray(m) {0L}
    for (i in 0..n - 1)
        for (j in 0..m - 1) {
            r[i] = r[i] + a[i][j]
            c[j] = c[j] + a[i][j]
        }

    var res = LongArray(q + 1) {0L}
    for (qq in 0..q) {
        var si = 0
        var sj = 0
        var sum = 0L
        var ans = 0L
        while (2 * (sum + r[si]) < total)
            sum += r[si++]
        sum = 0L
        while (2 * (sum + c[sj]) < total)
            sum += c[sj++]
        for (i in 0..n - 1)
            ans += r[i] * Math.abs(i - si)
        for (j in 0..m - 1)
            ans += c[j] * Math.abs(j - sj)
        res[qq] = ans
        if (qq < q) {
            var (i, j, x) = readln(); --i; --j;
            val delta = x - a[i][j]
            total += delta
            r[i] = r[i] + delta
            c[j] = c[j] + delta
            a[i][j] += delta
        }
    }
    writeln(res.joinToString(" "))
}

private fun PrintWriter.readSolveWrite() {
    val t = 1
    for (q in 1..t) {
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
