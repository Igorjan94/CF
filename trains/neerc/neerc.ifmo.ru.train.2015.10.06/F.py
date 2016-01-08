import math
import sys
 
ax, ay, bx, by = map(int, open("lattice.in", "r").readline().split())
file = open("lattice.out", "w")
 
a2 = ax ** 2 + ay ** 2
b2 = bx ** 2 + by ** 2
ab = ax * bx + ay * by
if ab == 0:
    if a2 < b2:
        file.write("1 0")
    else:
        file.write("0 1")
    sys.exit()
def f(p, q):
    return a2 * (p ** 2) + 2 * ab * p * q + b2 * (q ** 2)
 
x = b2 / ab
y = a2 / ab
eps = 0.0000000001
a = [   math.floor(x), -1, math.ceil(x + eps), -1, -1, math.floor(y), -1, math.ceil(y + eps), 
    math.floor(x), 1, math.ceil(x + eps), 1, 1, math.floor(y), 1, math.ceil(y + eps), 0, 1, 1, 0]
mn = f(a[0], a[1])
i = 0
for j in range(2, len(a), 2):
    temp = f(a[j], a[j + 1])
    if mn > temp:
        mn = temp
        i = j
file.write(str(a[i]) + " " + str(a[i + 1]))