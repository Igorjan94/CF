import java.io.PrintWriter// {{{
import java.util.*
import kotlin.collections.*// }}}

const val MOD = 998244353

class Modular(var value: Int) {
    init {
        if ((value > MOD) or (value < -MOD))
            value %= MOD
        if (value < 0)
            value += MOD
    }

    constructor(other: Modular): this(other.value) {}

    constructor(num: Int, den: Int) : this(0) {
        var xor = Modular(den).xor(MOD - 2)
        xor *= Modular(num)
        value = xor.value
    }

    fun xor(deg: Int): Modular {
        var copy = Modular(value)
        var a = Modular(this.value)
        var n = deg - 1
        while (n > 0) {
            if ((n and 1) == 1)
                copy *= a
            a *= a
            n = n shr 1
        }
        return copy
    }

    operator fun div(t: Int): Modular = Modular(value) * Modular(t).inverse()
    operator fun plus(t: Int): Modular = Modular(value + t)
    operator fun minus(t: Int): Modular = Modular(value - t)
    operator fun times(t: Int): Modular = Modular(((value * 1L * t) % MOD).toInt())

    operator fun div(t: Modular): Modular = Modular(value) * t.inverse()
    operator fun plus(t: Modular): Modular = Modular(value + t.value)
    operator fun minus(t: Modular): Modular = Modular(value - t.value)
    operator fun times(t: Modular): Modular = Modular(((value * 1L * t.value) % MOD).toInt())

    fun inverse(): Modular {
        return Modular(1, value)
    }

    override fun equals(other: Any?): Boolean = if (other is Modular)
        value == other.value
    else
        false

    override fun hashCode(): Int {
        return value
    }

    override fun toString(): String {
        return value.toString()
    }
}

class Matrix(var n: Int, var value: Array<IntArray>) {
    fun inc(i: Int, j: Int) {
        value[i][j]++
    }

    constructor(n: Int): this(n, Array(n) { IntArray(n) {0} }) {
    }

    fun xor(deg: Int): Matrix {
        var copy = Matrix(n, value)
        var a = Matrix(n, value)
        var n = deg - 1
        while (n > 0) {
            if ((n and 1) == 1)
                copy *= a
            a *= a
            n = n shr 1
        }
        return copy
    }

    operator fun times(other: Matrix): Matrix {
        val ret = Matrix(n)
        for (i in 0 until n)
            for (j in 0 until n)
                for (k in 0 until n)
                    ret.value[i][j] = (ret.value[i][j] + ((value[i][k] * 1L * other.value[k][j]) % MOD).toInt()) % MOD
        return ret
    }
}

class Trie {
    var array: ArrayList<IntArray> = arrayListOf(IntArray(26) {-1})
    var term: ArrayList<Boolean> = arrayListOf(false)

    operator fun plus(s: String): Trie {
        var root = 0
        for (c in s) {
            val u = c.toInt() - 'a'.toInt()
            if (array[root][u] == -1) {
                array[root][u] = array.size
                array.add(IntArray(26) {-1})
                term.add(false)
            }
            root = array[root][u]
        }
        term[root] = true
        return this
    }

}

private fun run() {
    val (n, m) = readln()
    val ss = Array(n) { readLine()!! }
    var trie = Trie()
    ss.forEach { trie += it }
    var init = Matrix(162)

    val q = LinkedList<Pair<Int, Int>>()
    val num = HashMap<Pair<Int, Int>, Int>()
    fun get(U: Int, V: Int): Int {
        var u = U
        var v = V
        if (u > v) {
            val t = u
            u = v
            v = t
        }
        val key = Pair(u, v)
        if (!num.containsKey(key)) {
            val value = num.size
            num[key] = value
            q.push(key)
        }
        return num[key]!!
    }

    val start = Pair(0, 0)
    q.add(start)
    num[start] = 0
    while (!q.isEmpty()) {
        val (u, v) = q.removeFirst()
        val x = get(u, v)
        for (i in 0..25) {
            val tou = trie.array[u][i]
            val tov = trie.array[v][i]
            if (tou == -1 || tov == -1)
                continue
            init.inc(x, get(tou, tov))
            if (trie.term[tou]) init.inc(x, get(0, tov))
            if (trie.term[tov]) init.inc(x, get(tou, 0))
            if (trie.term[tou] && trie.term[tov]) init.inc(x, get(0, 0))
        }
    }

    init = init.xor(m)
    writeln(init.value[0][0])
//    writeln(init.value.map { it.joinToString(" ") }.joinToString("\n"))
}

private fun PrintWriter.readSolveWrite() {
    run()
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
