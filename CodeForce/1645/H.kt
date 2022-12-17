import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    val (n) = readln()
    val a = readln()
    if (n == 1) {
        writeln("0")
        return
    }
    if (n == 2) {
        writeln("0 1")
        return
    }
    var allStates = ArrayList<Triple<Int, Int, Int>>()
    allStates.add(Triple(-1, -1, -1))

    var states = ArrayList<Int>()
    states.add(0)
    for (i in 0 until n) {
        var newStates = ArrayList<Int>()
        for (state in states) {
            val (l, r, _) = allStates[state]
            if (l == -1 || a[l] < a[i]) {
                newStates.add(allStates.size)
                allStates.add(Triple(i, r, state))
            }
            if (r == -1 || a[r] > a[i]) {
                newStates.add(allStates.size)
                allStates.add(Triple(l, i, state))
            }
        }
        states = ArrayList<Int>()
        val l = newStates.size
        for (j in max(0, l - 2) until l)
            states.add(newStates[j])
    }
    if (states.size == 0) {
        writeln("NO")
        return
    }
    val ans = IntArray(n) {0}
    var p = states.first()
    while (p != -1) {
        val (_, r, parent) = allStates[p]
        if (r != -1)
            ans[r] = 1
        p = parent
    }
    writeln("YES")
    writeln(ans.joinToString(" "))
}

private fun PrintWriter.readSolveWrite() {
    for (q in 1..1) {
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
