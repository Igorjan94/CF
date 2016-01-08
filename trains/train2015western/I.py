import sys
import math
r = int(input())
R = r ** 2
ans = -1
INF = 10 ** 9 + 2015
prev = 0
x = 0
for y in range(r - 1, 0, -1):
    Y = y ** 2
    while x ** 2 + Y <= R:
        x += 1
    t = y + 2 * Y
    x -= 1
    dx = x - prev
    if ans == -1:
        ans = (x * (2 * x + 1) * t) % INF
    elif dx > 0:
        ans = (ans + dx * (2 * dx + 1 + prev * 4) * t) % INF
    prev = x
if ans == -1:
    ans = 0
print(ans % INF)
