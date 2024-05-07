import java.io.PrintWriter// {{{
    import kotlin.math.*
    import kotlin.collections.*// }}}

private fun run() {
    var s = readLine()!!
    val n = s.length
    var a = ArrayList<Pair<Char, Int>>()
    for (i in 1 until n - 1) {
        a.add(Pair(s[i], i))
    }
    val b = a.sortedWith(compareBy({ it.first }, { it.second }))
    var first = s[0]
    var last = s.last()
    var needReverse = false
    if (first > last) {
        var t = first
        first = last
        last = t
        needReverse = true
    }
    var ans = ArrayList<Int>()
    var i = 0
    var j = 0
    while (i < b.size && b[i].first < first)
        i += 1
    while (j < b.size && b[j].first <= last)
        j += 1
    for (k in i until j)
        ans.add(b[k].second + 1)
    if (needReverse)
        ans.reverse()
    ans.add(0, 1)
    ans.add(n)
    writeln(last.code - first.code, ans.size)
    writeln(ans.joinToString(" "))
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

