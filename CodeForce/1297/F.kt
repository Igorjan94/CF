import java.io.*
import java.util.*
import kotlin.math.*
import kotlin.collections.*

fun main() = bufferOut { readSolveWrite() }

private fun PrintWriter.readSolveWrite() {
    fun writeln(vararg strings: Any) {
        println(strings.map{if (it is IntArray) it.joinToString(" ") else it}.joinToString(" "))
    }
    val (t) = getIntArray()
    test@for (q in 1..t) {
        val (n, m) = getIntArray()
        val a = CMap<Int, ArrayList<Pair<Int, Int>>>{ArrayList<Pair<Int, Int>>()}
        var c = IntArray(n, {0})
        val ans = IntArray(n, {0})
        for (i in 0..n - 1) {
            val (x, y) = getIntArray()
            a[x].add(Pair(y, i))
            c[i] = x
        }
        c.sort()
        val positions = c.distinct()
        var time = 0
        var opened = TreeSet<Pair<Int, Int>>(compareBy({it.first}, {it.second}))
        var answer = 0

        for (position in positions) {
            if (time > position)
                continue
            time = position
            opened.addAll(a[position])
            var counter = 0
            while (opened.size > 0) {
                val o = opened.firstOrNull()!!
                ans[o.second] = time
                answer = Math.max(answer, time - o.first)
                opened.remove(o)
                if (++counter % m == 0)
                    opened.addAll(a[++time])
            }
        }
        writeln(answer)
        writeln(ans)
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
