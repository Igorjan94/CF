import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    val (n) = readln()
    val a = Array(n) { readLine()!!.split(" ")}
    var mn = 100000000
    var mx = -1
    for ((s, t, r) in a) {
        var k = 0
        for (i in s.indices)
            if (i < t.length)
                if (s[s.length - i - 1] == t[t.length - i - 1])
                    k++
                else
                    break
        if (r == "1")
            mn = min(mn, k)
        else
            mx = max(mx, k)
    }
    if (mx < mn) {
        writeln(mn - mx)
        val ans = ArrayList<Int>()
        for (i in mx + 1..mn)
            ans.add(i)
        writeln(ans.joinToString(" "))
    } else {
        writeln(0)
    }
}

private fun PrintWriter.readSolveWrite() {
    val (t) = readln()
    repeat(t) {
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
            @OptIn(kotlin.ExperimentalStdlibApi::class)
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
