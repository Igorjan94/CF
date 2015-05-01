import sys
import collections

result = [(0, 0)] * 200010
ls = [(0, 0)] * 200010
toget = []

def inverses_merge(l1, r1, l2, r2):
    counter = l1
    l = l1
    while (l1 < r1) and (l2 < r2):
        if ls[l1][0] < ls[l2][0]:
            result[counter] = ls[l1]
            l1 += 1
        else:
            result[counter] = ((ls[l2][0], ls[l2][1] + r1 - l1))
            l2 += 1
        counter += 1
    while l1 < r1:
        result[counter] = ls[l1]
        counter += 1
        l1 += 1
    while l2 < r2:
        result[counter] = ls[l2]
        counter += 1
        l2 += 1
    for i in range(l, counter, 1):
        ls[i] = result[i]

def inverses_get(l, r):
    if r - l == 0:
        return
    if r - l == 1:
        ls[l] = (toget[l], 0)
        return
    m = (l + r) // 2
    inverses_get(l, m)
    inverses_get(m, r)
    inverses_merge(l, m, m, r)

n = int(sys.stdin.readline())
d = {}
for i in range(n):
    x, y = list(map(int, sys.stdin.readline().split()))
    if not d.__contains__(x):
        d[x] = x
    if not d.__contains__(y):
        d[y] = y
    t = d[x]
    d[x] = d[y]
    d[y] = t
index = {}
d = collections.OrderedDict(sorted(d.items()))
i = 0

for t in (d.items()):
    toget.append(t[1])
    index[t[1]] = i
    i += 1

s = 0
inverses_get(0, len(toget))
x = result
for i in range(len(toget)):
    s += x[i][1]
    s += abs(x[i][0] - d[x[i][0]]) - abs(i - index[x[i][0]])
sys.stdout.write(str(s) + "\n")
