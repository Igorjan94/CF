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
        val (n) = getIntArray()
        val a = getIntArray()
        var mn = 100000
        var mx = -100000
        var i1 = -1
        var i2 = -1
        var s = IntArray(n, {0})
        var sum = 0L
        for (i in 0 .. n - 1) {
            val x = a[i]
            if (x > 0) {
                sum += x
                s[i] = 1
                if (mn > x) {
                    mn = x
                    i1 = i
                }
            }
            if (x < 0)
                if (x > mx) {
                    mx = x
                    i2 = i
                }
        }
        //writeln(mn, mx, i1, i2)
        if ((i1 != -1) and (mn < -mx) or (i2 == -1)) {
            s[i1] = 0
            sum -= a[i1]
        } else {
            s[i2] = 1
            sum += a[i2]
        }
        writeln(sum)
        writeln(s.joinToString(""))
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
