import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    val (n, m, d) = readln()
    val c = readln()
    val a = IntArray(n, {0})
    val b = IntArray(n, {0})
    val s = IntArray(m, {-1})

    var j = n - 1
    for (i in m - 1 downTo 0) {
        for (k in 0..c[i] - 1)
            b[j - k] = i + 1
        j -= c[i]
        s[i] = j + 1
    }

    j = -1
    for (i in 0..m - 1) {
        j += d
        if (j >= s[i]) {
            for (k in s[i]..n - 1)
                a[k] = b[k]
            j = n
            break
        }
        for (k in 0..c[i] - 1)
            if (j + k < n)
                a[j + k] = i + 1
        j += c[i] - 1
    }
    if (j + d >= n) {
        writeln("YES")
        writeln(a.joinToString(" "))
    } else {
        writeln("NO");
    }
}

private fun PrintWriter.readSolveWrite() {
    run()
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
