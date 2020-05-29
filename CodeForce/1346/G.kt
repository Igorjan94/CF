import java.io.PrintWriter// {{{
import kotlin.math.*
import kotlin.collections.*// }}}

private fun run() {
    tailrec fun gcd(a: Int, b: Int): Int {
        return if (b == 0) a else gcd(b, a % b)
    }

    val (n, k) = readln()
    val p = readln()
    val a = readln()
    if (k == 2) {
        writeln("YES")
        writeln(a[0], p.first())
        writeln(a[1], p.first())
        return
    }

    fun check(first: Int, second: Int): Pair<Pair<Int, Int>, Pair<Int, Int>> {
        var no = Pair(Pair(-1, -1), Pair(-1, -1))

        var s1 = first
        for (d1 in p)
            if ((second - s1) % d1 == 0) {
                var s2 = -1
                var last = -1
                var g = 0
                for (x in a)
                    if ((x - s1) % d1 != 0) {
                        if (last != -1)
                            g = gcd(g, x - last)
                        else
                            s2 = x
                        last = x
                    }

                if (last == -1) // Empty
                    return Pair(Pair(s1, d1), Pair(a[0], p.first()))
                if (g == 0) // One left
                    return Pair(Pair(s1, d1), Pair(last, p.first()))
                for (d2 in p) // More than one left
                    if (g % d2 == 0)
                        return Pair(Pair(s1, d1), Pair(s2, d2))
            }
        return no
    }

    var os = check(a[0], a[1])
    if (os.first.first != -1) {
        writeln("YES")
        writeln(os.first.first, os.first.second);
        writeln(os.second.first, os.second.second);
        return
    }
    os = check(a[0], a[2])
    if (os.first.first != -1) {
        writeln("YES")
        writeln(os.first.first, os.first.second);
        writeln(os.second.first, os.second.second);
        return
    }
    os = check(a[1], a[2])
    if (os.first.first != -1) {
        writeln("YES")
        writeln(os.first.first, os.first.second);
        writeln(os.second.first, os.second.second);
        return
    }
    writeln("NO")
}

private fun PrintWriter.readSolveWrite() {
    val t = 1
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
