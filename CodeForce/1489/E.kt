import java.io.PrintWriter// {{{
import kotlin.collections.*// }}}
import kotlin.math.min

private fun run() {
    val (n) = readln()
    val m = HashMap<Int, Triple<Char, Int, Int>>()
    var l = 0
    var r = 0
    for (q in 0 until n) {
        val s = readLine()!!
        val c = s[0]
        val i = s.substring(2).toInt()

        if (c == '?') {
            val p = m[i]!!
            if (p.first == 'L')
                writeln(min(l - p.second - 1, r + p.second))
            else
                writeln(min(l + p.third, r - p.third - 1))
        } else {
            m[i] = Triple(c, l, r)
            if (c == 'L') l++; else r++
        }
    }
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
