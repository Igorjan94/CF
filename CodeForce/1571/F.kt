import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    val (n, m) = readln()
    var a = Array(n) { readln() }.withIndex().sortedWith(compareBy({ it.value[1] }, { -it.value[0] }))
    val ans = IntArray(n) { -1 }
    var prev = 1
    for (i in a.indices)
        if (a[i].value[1] == 1) {
            ans[a[i].index] = prev
            prev += a[i].value[0]
        }
    a = a.dropWhile { it.value[1] == 1 }
    val sum = a.sumOf { it.value[0] }
    val y = sum / 2 + 1
    if (sum > m)
        return writeln(-1)
    var pprev = prev + 1
    val dp = BooleanArray(y) { false }
    val par = IntArray(y) { -1 }
    dp[0] = true
    for (i in a.indices) {
        val x = a[i].value[0]

        for (j in y - 1 downTo 0)
            if (dp[j] and (j + x < y))
                if (!dp[j + x]) {
                    dp[j + x] = true
                    par[j + x] = i
                }
    }
    for (i in y - 1 downTo 0) {
        if (dp[i]) {
            if (i < sum - i) {
                val t = prev
                prev = pprev
                pprev = t
            }
            var p = i
            while (p > 0) {
                val index = par[p]
                ans[a[index].index] = prev
                prev += a[index].value[0] * 2
                p -= a[index].value[0]
            }

            for (j in a.indices)
                if (ans[a[j].index] == -1) {
                    ans[a[j].index] = pprev
                    pprev += a[j].value[0] * 2
                }
            return if (max(prev, pprev) > m + 2)
                writeln(-1)
            else
                writeln(ans.joinToString(" "))
        }
    }

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
