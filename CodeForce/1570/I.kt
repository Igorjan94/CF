import java.io.PrintWriter// {{{
import java.lang.Integer.min
import kotlin.collections.*// }}}

private const val MAX_N = 100_001
private const val P = 2000

private val cnt = IntArray(MAX_N) { 0 }
private val ord = IntArray(MAX_N) { 0 }
private val bounds = Array(MAX_N) { Point(MAX_N, 0) }

data class Query(val t: Int, val l: Int, val r: Int, val k: Int, var index: Int)
data class Update(val index: Int, val from: Int, val to: Int)
data class Point(var x: Int, var y: Int)

private fun run() {
    val (n, m) = readln()
    val a = readln()
    val queries = ArrayList<Query>()
    val updates = ArrayList<Update>()

    repeat(m) {
        val request = readln()
        var (t, l, r) = request
        l -= 1
        if (t == 1) {
            queries.add(Query(updates.size, l, r - 1, request[3], queries.size))
        } else {
            updates.add(Update(l, a[l], r))
            a[l] = r
        }
    }
    for ((i, from) in updates.reversed())
        a[i] = from

    val ans = IntArray(queries.size)
    queries.sortWith(compareBy({ it.t / P }, { it.l / P }, { it.r }))
    bounds[0] = Point(0, MAX_N - 1)
    var L = 0
    var R = -1
    var T = 0

    fun next(i: Int) = bounds[ord[i]].y + 1
    fun count(i: Int) = bounds[ord[i]].y - bounds[ord[i]].x + 1

    fun add(x: Int) {
        val c = cnt[x]++
        ord[bounds[c].x]++
        bounds[c + 1].y = bounds[c].x
        if (bounds[c + 1].x == MAX_N)
            bounds[c + 1].x = bounds[c].x
        if (bounds[c].x == bounds[c].y)
            bounds[c].x = MAX_N - 1
        ++bounds[c].x
    }
    fun del(x: Int) {
        val c = cnt[x]--
        ord[bounds[c].y]--
        if (bounds[c - 1].x == MAX_N)
            bounds[c - 1].y = bounds[c].y
        bounds[c - 1].x = bounds[c].y
        if (bounds[c].x == bounds[c].y)
            bounds[c].x = MAX_N
        --bounds[c].y
    }
    fun update(index: Int, forward: Boolean) {
        var (i, from, to) = updates[index]
        if (!forward) to = from
        if (i in L..R) {
            del(a[i])
            add(to)
        }
        a[i] = to
    }
    for ((t, l, r, k, id) in queries) {
        while (T < t) update(T++, true)
        while (T > t) update(--T, false)
        while (R < r) add(a[++R])
        while (L > l) add(a[--L])
        while (R > r) del(a[R--])
        while (L < l) del(a[L++])
        var res = MAX_N
        var i = 0
        var j = 0
        var sum = 0

        while (i < MAX_N && ord[i] > 0) {
            while (j < MAX_N && ord[j] > 0 && sum < k) {
                sum += count(j)
                j = next(j)
            }
            if (sum >= k)
                res = min(res, ord[i] - ord[j - 1])
            sum -= count(i)
            i = next(i)
        }
        if (res == MAX_N)
            ans[id] = -1
        else
            ans[id] = res
    }
    writeln(ans.joinToString("\n"))
}

private fun PrintWriter.readSolveWrite() {
    run()
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
