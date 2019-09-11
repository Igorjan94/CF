import java.io.*
import kotlin.math.*
import kotlin.collections.*

fun main() = bufferOut { readSolveWrite() }

private fun PrintWriter.readSolveWrite() {
    val (n) = getIntArray()
    var a = arrayListOf<Triple<Int, Int, Int>>()
    var t = arrayListOf<Pair<Int, Int>>()
    for (i in 1..n) {
        val (c, p) = getIntArray()
        a.add(Triple(c, p, i))
    }
    val (w) = getIntArray()
    val x = getIntArray()
    for (i in 1..w)
        t.add(Pair(x[i - 1], i))

    a.sortBy{it.first}
    t.sortBy{it.first}
    val A = Array(n + 1, {IntArray(w + 1)})
    for (i in 0..w)
        A[0][i] = 0
    for (i in 0..n)
        A[i][0] = 0
    for (k in 1..n)
        for (s in 1..w)
            if (t[s - 1].first >= a[k - 1].first)
                A[k][s] = max(A[k - 1][s], A[k - 1][s - 1] + a[k - 1].second)
            else 
                A[k][s] = A[k - 1][s]

    var ans = arrayListOf<Pair<Int, Int>>()
    fun findAns(k: Int, s: Int) {
        if (A[k][s] == 0)
            return
        if (A[k - 1][s] == A[k][s])
            findAns(k - 1, s)
        else {
            findAns(k - 1, s - 1)
            ans.add(Pair(a[k - 1].third, t[s - 1].second))
        }
    }
    findAns(n, w)
    println("" + ans.size + " " + A[n][w])
    println(ans.map{"" + it.first + " " + it.second}.joinToString("\n"))
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
