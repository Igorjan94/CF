import java.io.PrintWriter// {{{
    import kotlin.math.*
    import kotlin.collections.*// }}}

private fun run() {
    var (N, c) = readLine()!!.split(' ')
    var n = N.toInt()
    val n2 = n * 2
    var s = readLine()!!
    s += s
    val a = IntArray(n2) {-1}
    var last = n2
    for (i in n2 - 1 downTo 0) {
        if (s[i] == 'g')
            last = i
        a[i] = last
    }
    var ans = 0
    for (i in 0 until n)
        if (s[i] == c[0])
            ans = Math.max(ans, a[i] - i)
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

