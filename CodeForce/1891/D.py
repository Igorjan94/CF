
def f(x):
    i = 0
    deg = 1
    while deg * 2 <= x:
        i += 1
        deg *= 2
    return i

def g(x):
    fx = f(x)
    i = 0
    deg = 1
    while (deg <= x):
        i += 1
        deg *= fx
    return i - 1

def run():
    q = int(input())
    a = []
    cur = 8
    fx = 2
    for i in range(2, 66):
        l = cur
        cur *= 2
        fx += 1
        z = 0
        fxd = 1
        while (fxd < cur):
            if (fxd >= l):
                a.append([fxd, z])
            z += 1
            fxd *= fx
        a.append([l, g(l)])
    a.sort()
    a = a[1:]
    b = [a[0]]
    for i in range(1, len(a)):
        if (a[i][1] != b[-1][1]):
            b.append(a[i])
    a = b
    print(*a, sep = '\n')

    def get(x):
        if (x < 4): return 0
        if (x < 8): return (x - 3) * 2
        if (x == 8): return 9
        ans = 9
        i = 1
        while i < len(a) and x >= a[i - 1][0]:
            ans += a[i - 1][1] * (min(x, a[i][0] - 1) - a[i - 1][0] + 1)
            i += 1
            ans %= 1000000007
        return ans
    for Q in range(q):
        [l, r] = map(int, input().split())
        print(get(r) - get(l - 1))

run()
