import java.io.PrintWriter// {{{
    import kotlin.math.*
    import kotlin.collections.*// }}}

private fun run() {
    readLine()!!
    val (n, m) = readln()
    val a = readln().toMutableList()
    a.add(-1)
    val p = sortedSetOf<Int>()
    val o = sortedSetOf<Int>()
    var last = a[0] + 1
    for (i in 0 .. n)
        if (a[i] < last) {
            last = a[i]
            p.add(i)
            o.add(-i)
        }
    val ans = IntArray(m) {0}
    for (q in 0 until m) {
        var (k, d) = readln()
        k -= 1
        val nxt = a[k] - d
        val l = -o.ceiling(-k)
        var r = p.ceiling(k + 1)
        if (nxt < a[l]) {
            while (nxt <= a[r]) {
                o.remove(-r)
                p.remove(r)
                r = p.ceiling(k + 1)
            }
            p.add(k)
            o.add(-k)
        }
        a[k] -= d
        ans[q] = p.size - 1
    }
    writeln(ans)
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
            val d = c.code - '0'.code
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
