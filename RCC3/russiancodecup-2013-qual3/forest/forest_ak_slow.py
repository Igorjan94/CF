from sys import *
from collections import Counter
from fractions import *
n = int(input())

def proc(c):
    p = Fraction(1)
    for i in c:
        p *= 1 - Fraction(1, i)
    return 1 - p

def solve(n, m):
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
    res = 0
    for c, n in spectre.items():
        res += proc(c) * n
    return res

for t in range(n):
    a, b = map(int, input().split())
    print (a, b, file=stderr)
    print (solve(a, b))
