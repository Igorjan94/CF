import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    var (n, m, k) = readln(); --k
    var ans = IntArray(n) {-1}
    for (i in 1..m) {
        var (u, v) = readln(); --u; --v
        if (u == k) {
            ans[u] = 1
            ans[v] = 0
            k = v
            continue
        }
        if (v == k) {
            ans[v] = 1
            ans[u] = 0
            k = u
            continue
        }
        if ((ans[u] == -1) and (ans[v] == -1))
            continue
        if (ans[v] == -1) {
            ans[v] = ans[u]
            ans[u]++
            continue
        }
        if (ans[u] == -1) {
            ans[u] = ans[v]
            ans[v]++
            continue
        }
        if ((ans[u] != -1) and (ans[v] != -1)) {
            val xxx = Math.min(ans[u] + 1, ans[v])
            val yyy = Math.min(ans[v] + 1, ans[u])
            ans[u] = xxx
            ans[v] = yyy
        }
    }

    writeln(ans)
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
