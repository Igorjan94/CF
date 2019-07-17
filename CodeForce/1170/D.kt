import java.io.*// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun PrintWriter.readSolveWrite() {
    val (m) = readln()
    val a = readln()
    val n = a.count{it == -1}
    var temp = Array(n) { ArrayList<Int>() }
    var s = sortedSetOf<Int>()
    for (i in 0..n - 1)
        s.add(i)
    var it = s.iterator()
    for (i in 0..m - 1) {
        if (!it.hasNext())
            it = s.iterator()
        val x = it.next()
        if (a[i] == -1)
            it.remove()
        else
            temp[x].add(a[i])
    }

    writeln(n)
    for (i in 0..n - 1)
        writeln(temp[i].size, temp[i].joinToString(" "))
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
