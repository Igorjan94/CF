import sys
import math

n = int(input())
a = list(map(int, input().split()))
s = sum(a)
if s % n != 0:
    print('Impossible')
    sys.exit()

m = s // n
g = sum((x - m) ** 2 for x in a)
if g % n != 0:
    print('Impossible')
    sys.exit()

g //= n
for (i, x) in enumerate(a):
    X = x - m
    K = g + X ** 2
    D = s + X
    c = m ** 2 + D ** 2 - K
    b = 2 * (m + D)
    d = b ** 2 - 8 * c
    if d < 0: continue
    sk = max(0, int(math.sqrt(d)) - 1)
    while sk ** 2 < d: sk += 1
    if sk ** 2 == d:
        a = 2 * (m + D) + sk
        if a % 4 == 0:
            a //= 4
            b = s + x - a
            print('Possible')
            print(i + 1, a, b)
            sys.exit()

print('Impossible')
