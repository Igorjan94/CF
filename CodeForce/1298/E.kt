import java.io.*
import kotlin.math.*
import kotlin.collections.*

fun main() = bufferOut { readSolveWrite() }

private fun PrintWriter.readSolveWrite() {
    fun writeln(vararg strings: Any) {
        println(strings.map{if (it is IntArray) it.joinToString(" ") else it}.joinToString(" "))
    }
    val (n, k) = getIntArray()
    val score = getIntArray()
    val bad = Array<ArrayList<Int>>(n, {ArrayList<Int>()})
    for (i in 0..k - 1) {
        var (u, v) = getIntArray()
        --u
        --v
        if (score[u] > score[v])
            bad[u].add(v)
        else if (score[v] > score[u])
            bad[v].add(u)
    }
    val ans = IntArray(n, {0})
    val b = score.zip(0..n - 1).sortedBy{it.first}

    var cnt = 1
    var last = 0
    for (i in 1..n - 1)
        if (b[i - 1].first == b[i].first) {
            ans[b[i].second] = last
            cnt++
        } else {
            ans[b[i].second] = last + cnt
            cnt = 1
            last = ans[b[i].second]
        }

    val was = mutableSetOf<Int>()
    for ((_, u) in b) {
        for (v in bad[u])
            if (was.contains(v))
                ans[u]--
        was.add(u)
    }
    writeln(ans)
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
