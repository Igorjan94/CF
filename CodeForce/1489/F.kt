import java.io.PrintWriter// {{{
import kotlin.collections.*// }}}

private fun binSearch(L: Int, R: Int, f: (Int) -> Boolean): Int {
    var l = L
    var r = R
    var m: Int
    while (r - l > 1) {
        m = l + (r - l) / 2
        if (f(m))
            r = m
        else
            l = m
    }
    return if (f(l)) l else r
}

private fun run() {
    val (n, m, k) = readln()
    val a = readln()
    writeln(-1 + binSearch(0, n + 1) {
        var cur = 0
        var sum = 0
        for (i in n - it until n) {
            if (sum + a[i] <= k)
                sum += a[i]
            else {
                sum = a[i]
                cur++
            }
        }
        if (sum != 0) cur++
        cur > m
    })
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
