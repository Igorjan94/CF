import math

def solve(b, c):
    d = b * b - 4 * c
    if d < 0:
        return None
    s = int(math.sqrt(d))
    while (s * s < d): s += 1
    while (s * s > d): s -= 1
    if s * s != d:
        return None
    q = -b + s
    w = -b - s
    if q % 2 != 0:
        return None
    if w % 2 != 0:
        return None
    return [-q // 2, -w // 2]


def run():
    n = int(input())
    a = list(map(int, input().split()))
    D = {}
    for x in a:
        D[x] = D.get(x, 0) + 1

    ans = []
    q = int(input())
    for Q in range(q):
        b, c = list(map(int, input().split()))
        cur = solve(b, c)
        if cur is None:
            ans.append(0)
        else:
            x, y = cur
            w = D.get(x, 0)
            e = D.get(y, 0)
            if x == y:
                ans.append(w * (w - 1) // 2)
            else:
                ans.append(w * e)
    print(*ans)

t = int(input())
for i in range(t):
    run()
