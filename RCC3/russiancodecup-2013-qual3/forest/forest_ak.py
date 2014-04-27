from collections import Counter
from fractions import *
n = int(input())

def proc(c):
    p = Fraction(1)
    for i in c:
        p *= 1 - Fraction(1, i)
    return 1 - p

def calc(spectre):
    res = 0
    for c, n in spectre.items():
        res += proc(c) * n
    return res

def solve_slow(n, m):
    def neighb(x, y):
        res = 0
        if x > 0: res += 1
        if x < n - 1: res += 1
        if y > 0: res += 1
        if y < m - 1: res += 1
        return res
    def inBounds(x, y):
        return 0 <= x < n and 0 <= y < m
    spectre = Counter()
    for i in range(n):
        for j in range(m):
            ne = ()
            for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                x = i + dx
                y = j + dy
                if not inBounds(x, y):
                    continue
                ne += (neighb(x, y), )
            ne = tuple(sorted(ne))
            spectre[ne] += 1
    return calc(spectre)

def solve1(n):
    res = Counter()
    res[(2, )] = 2
    res[(1, 2)] = 2
    res[(2, 2)] = n - 4
    return calc(res)

def solve2(n):
    res = Counter()
    res[(2, 3)] = 4
    res[(2, 3, 3)] = 4
    res[(3, 3, 3)] = 2 * (n - 4)
    return calc(res)

def solve3(n):
    res = Counter()
    res[(3, 3)] = 4
    res[(2, 2, 4)] = 2
    res[(3, 3, 3, 4)] = 2
    res[(2, 3, 4)] = 4
    res[(3, 3, 4)] = 2 * (n - 4)
    res[(3, 3, 4, 4)] = n - 4
    return calc(res)

def solve(n, m):
    if n < 4 and m < 4:
        return solve_slow(n, m)
    if n > m:
        return solve(m, n)
    if n == 1:
        return solve1(m)
    if n == 2:
        return solve2(m)
    if n == 3:
        return solve3(m)
    res = Counter()
    res[(3, 3)] = 4
    res[(2, 3, 4)] = 8
    res[(3, 3, 4)] = 2 * n + 2 * m - 16
    res[(3, 3, 4, 4)] = 4
    res[(3, 4, 4, 4)] = 2 * (n - 4) + 2 * (m - 4)
    res[(4, 4, 4, 4)] = (n - 4) * (m - 4)
    return calc(res)


for t in range(n):
    a, b = map(int, input().split())
    print (solve(a, b))
