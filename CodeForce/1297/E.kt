import java.io.*
import kotlin.math.*
import kotlin.collections.*

fun main() = bufferOut { readSolveWrite() }

private fun PrintWriter.readSolveWrite() {
    fun writeln(vararg strings: Any) {
        println(strings.map{if (it is IntArray) it.joinToString(" ") else it}.joinToString(" "))
    }
    val (t) = getIntArray()
    for (q in 1..t) {
        var (n, k) = getIntArray()
        val g = Array<ArrayList<Int>>(n, {ArrayList<Int>()})
        val d = IntArray(n, {0})
        val used = IntArray(n, {0})
        repeat(n - 1) {
            var (u, v) = getIntArray()
            --u; --v
            d[u]++
            d[v]++
            g[u].add(v)
            g[v].add(u)
        }
        val ans = ArrayList<Int>()
        fun dfs(u: Int) {
            ans.add(u + 1)
            used[u] = 1
            for (v in g[u])
                if (used[v] == 0) {
                    dfs(v)
                    break
                }
            for (v in g[u])
                if ((k > 0) and (used[v] == 0)) {
                    --k
                    dfs(v)
                }
        }
        if (k == 1) {
            writeln("Yes")
            writeln(1)
            writeln(1)
            continue
        }
        for (i in 0 .. n - 1)
            if (d[i] == 1) {
                --k
                --k
                dfs(i)
                break
            }
        if (k <= 0) {
            writeln("Yes")
            writeln(ans.size)
            writeln(ans.joinToString(" "))
        } else
            writeln("No")
    }
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun getIntArray() = readLine()!!.splitToIntArray()

private fun bufferOut(block: PrintWriter.() -> Unit) = PrintWriter(System.out).use { block(it) }

class CMap<K,V>(val m: HashMap<K,V> = HashMap<K,V>(), val def: () -> V) {
    operator fun get(k: K): V = m.getOrPut(k, def)
    operator fun set(k: K, v: V) = m.put(k, v)
}

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
