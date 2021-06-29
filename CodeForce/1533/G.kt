import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    val (n, m) = readln()
    val a = Array(n) { readln() }
    for (i in 0 until n)
        for (j in 0 until m)
            if (a[i][j] != 0) {
                val used = Array(n) {Array(m) {false} }
                val ans = ArrayList<Int>()
                fun dfs(i: Int, j: Int) {
                    ans.add(a[i][j])
                    used[i][j] = true
                    for (dx in -1..1)
                        for (dy in -1..1)
                            if (dx * dx + dy * dy == 1) {
                                val u = i + dx
                                val v = j + dy
                                if (u < 0 || u == n || v < 0 || v == m || a[u][v] == 0 || used[u][v])
                                    continue
                                dfs(u, v)
                                ans.add(a[i][j])
                            }
                }
                dfs(i, j)
                for (q in 0 until n)
                    for (w in 0 until m)
                        if (a[q][w] != 0 && !used[q][w]) {
                            writeln(-1)
                            return
                        }
                val l = ans.size / 2 + 1
                writeln(l, l)
                for (q in 0 until l)
                    writeln(ans.subList(q, q + l).joinToString(" "))
                return
            }
}

private fun PrintWriter.readSolveWrite() {
    val (t) = readln()
    for (q in 1..t) {
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
