import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    val (n, m) = readln()
    val mp = mutableMapOf<String, Int>()
    val firsts = mutableMapOf<Int, Int>()
    val lasts = mutableMapOf<Int, Int>()
    var myf = 0
    var myl = 0
    repeat(m) {
        val (f, l) = readln()
        if (it == 0) {
            myf = f
            myl = l
        }
        val vote = "$f $l"
        mp[vote] = mp.getOrDefault(vote, 0) + 1
        firsts[f] = firsts.getOrDefault(f, 0) + 1
        lasts[l] = lasts.getOrDefault(l, 0) + 1
    }
    var ans = 1
    for (f in 1..n)
        for (l in 1..n)
            if (f != l) {
                val c0 = mp.getOrDefault("$f $l", 0)
                val c1 = firsts.getOrDefault(f, 0) + lasts.getOrDefault(l, 0) - 2 * c0
                if ((f == myf) and (l == myl))
                    ans = max(ans, 1)
                else if ((f == myf) or (l == myl))
                    ans = max(ans, c0 + 1)
                else
                    ans = max(ans, c0 + c1 + 1)
            }
    writeln(ans)
}

private fun PrintWriter.readSolveWrite() {
//    val (t) = readln()
    repeat(1) {
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
