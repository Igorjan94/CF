import java.io.PrintWriter// {{{
import kotlin.collections.*// }}}

class DSU(n: Int) {

    private var a = IntArray(n)
    private var sz = IntArray(n) { 1 }

    init {
        for (i in a.indices) a[i] = i
    }

    fun get(i: Int): Int {
        return if (a[i] == i)
            i
        else {
            a[i] = get(a[i]);
            a[i]
        }
    }

    fun union(i: Int, j: Int): Boolean {
        var l = get(i)
        var r = get(j)
        if (l == r) return false
        if (sz[l] > sz[r]) {
            val t = l
            l = r
            r = t
        }
        sz[r] += sz[l]
        a[l] = r
        return true
    }
}

private fun run() {
    val (n, m) = readln()
    val a = readLine()!!.split(" ").map { it.toLong() }.zip(0..n).sortedBy { it.first }
    val b = Array(m) {
        val x = readLine()!!.split(" ").map { it.toLong() }
        Triple(x[0].toInt() - 1, x[1].toInt() - 1, x[2])
    }.sortedBy { it.third }
    var ans = 0L
    val d = DSU(n)
    var j = 0
    for (i in 1 until n) {
        val first = d.get(a[0].second)
        val second = d.get(a[i].second)
        if (first == second) continue
        while (j < m && b[j].third <= a[0].first + a[i].first) {
            if (d.union(b[j].first, b[j].second))
                ans += b[j].third
            ++j
        }
        if (d.union(a[0].second, a[i].second))
            ans += a[0].first + a[i].first
    }
    writeln(ans)
}

private fun PrintWriter.readSolveWrite() {
//    val (t) = readln()
    val t = 1
    for (q in 1..t) {
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
