import random
import math
import sys

n = 1400
m = 15000
c = 0
f = 14000
g = 4500

def genUV(n):
    u = random.randint(0, n - 1)
    while True:
        v = random.randint(0, n - 1)
        if u != v:
            return u, v

print(n, m, c, f)
for i in range(m):
    u, v = genUV(n)
    print(i, random.randint(0, g), u, v, random.randint(100, 1000), random.randint(1, 10 ** 5))

for i in range(f):
    u, v = genUV(n)
    print(i, u, v, random.randint(2, 12000))
