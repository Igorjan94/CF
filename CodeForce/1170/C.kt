import java.io.*// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun PrintWriter.readSolveWrite() {
    val (t) = readln()
    for (q in 1..t) {
        val s = readLine()!!
        val t = readLine()!!
        val n = s.length
        val m = t.length
        var j = 0
        var ok = true
        for (i in 0..m - 1) {
            if (j == n) {
                ok = false
                continue
            }
            if (s[j] == '+') {
                if (t[i] == '-')
                    ok = false
                else
                    j++
            } else {
                if (t[i] == '-')
                    j++
                else {
                    if (j + 1 < n && s[j + 1] == '-')
                        j += 2
                    else
                        ok = false
                }
            }
        }
        if (ok && j == n)
            writeln("YES");
        else
            writeln("NO");
    }
}

private fun ok(x: Boolean) = if (x) 1 else 0// {{{

private fun writeln(vararg params: Any) = println(params.joinToString(" "))

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
